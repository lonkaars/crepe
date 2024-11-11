#include <cmath>
#include <cstdlib>
#include <ctime>

#include "api/ParticleEmitter.h"
#include "api/Transform.h"
#include "api/Vector2.h"

#include "ComponentManager.h"
#include "ParticleSystem.h"

using namespace crepe;

ParticleSystem::ParticleSystem() {}

void ParticleSystem::update() {
	// Get all emitters
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<ParticleEmitter>> emitters
		= mgr.get_components_by_type<ParticleEmitter>();

	for (ParticleEmitter & emitter : emitters) {
		// Get transform linked to emitter
		const Transform & transform
			= mgr.get_components_by_id<Transform>(emitter.game_object_id)
				  .front()
				  .get();

		// Emit particles based on emission_rate
		int updates
			= calculate_update(this->update_count, emitter.data.emission_rate);
		for (size_t i = 0; i < updates; i++) {
			emit_particle(emitter, transform);
		}

		// Update all particles
		for (Particle & particle : emitter.data.particles) {
			if (particle.active) {
				particle.update();
			}
		}

		// Check if within boundary
		check_bounds(emitter, transform);
	}

	this->update_count = (this->update_count + 1) % this->MAX_UPDATE_COUNT;
}

void ParticleSystem::emit_particle(ParticleEmitter & emitter,
								   const Transform & transform) {
	constexpr double DEG_TO_RAD = M_PI / 180.0;

	Vector2 initial_position = emitter.data.position + transform.position;
	double random_angle
		= generate_random_angle(emitter.data.min_angle, emitter.data.max_angle);

	double random_speed
		= generate_random_speed(emitter.data.min_speed, emitter.data.max_speed);
	double angle_radians = random_angle * DEG_TO_RAD;

	Vector2 velocity = {random_speed * std::cos(angle_radians),
						random_speed * std::sin(angle_radians)};

	for (Particle & particle : emitter.data.particles) {
		if (!particle.active) {
			particle.reset(emitter.data.end_lifespan, initial_position,
						   velocity, random_angle);
			break;
		}
	}
}

int ParticleSystem::calculate_update(int count, double emission) const {
	double integer_part = std::floor(emission);
	double fractional_part = emission - integer_part;

	if (fractional_part > 0) {
		int denominator = static_cast<int>(1.0 / fractional_part);
		return (count % denominator == 0) ? 1 : 0;
	}

	return static_cast<int>(emission);
}

void ParticleSystem::check_bounds(ParticleEmitter & emitter,
								  const Transform & transform) {
	Vector2 offset = emitter.data.boundary.offset + transform.position
					 + emitter.data.position;
	double half_width = emitter.data.boundary.width / 2.0;
	double half_height = emitter.data.boundary.height / 2.0;

	const double LEFT = offset.x - half_width;
	const double RIGHT = offset.x + half_width;
	const double TOP = offset.y - half_height;
	const double BOTTOM = offset.y + half_height;

	for (Particle & particle : emitter.data.particles) {
		const Vector2 & position = particle.position;
		bool within_bounds = (position.x >= LEFT && position.x <= RIGHT
							  && position.y >= TOP && position.y <= BOTTOM);

		if (!within_bounds) {
			if (emitter.data.boundary.reset_on_exit) {
				particle.active = false;
			} else {
				particle.velocity = {0, 0};
				if (position.x < LEFT) particle.position.x = LEFT;
				else if (position.x > RIGHT) particle.position.x = RIGHT;
				if (position.y < TOP) particle.position.y = TOP;
				else if (position.y > BOTTOM) particle.position.y = BOTTOM;
			}
		}
	}
}

double ParticleSystem::generate_random_angle(double min_angle,
											 double max_angle) const {
	if (min_angle == max_angle) {
		return min_angle;
	} else if (min_angle < max_angle) {
		return min_angle
			   + static_cast<double>(std::rand()
									 % static_cast<int>(max_angle - min_angle));
	} else {
		double angle_offset = (360 - min_angle) + max_angle;
		double random_angle = min_angle
							  + static_cast<double>(
								  std::rand() % static_cast<int>(angle_offset));
		return (random_angle >= 360) ? random_angle - 360 : random_angle;
	}
}

double ParticleSystem::generate_random_speed(double min_speed,
											 double max_speed) const {
	if (min_speed == max_speed) {
		return min_speed;
	} else {
		return min_speed
			   + static_cast<double>(std::rand()
									 % static_cast<int>(max_speed - min_speed));
	}
}
