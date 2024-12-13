#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "../api/ParticleEmitter.h"
#include "../api/Transform.h"
#include "../manager/ComponentManager.h"
#include "../manager/LoopTimerManager.h"

#include "ParticleSystem.h"

using namespace crepe;

void ParticleSystem::update() {
	// Get all emitters
	const Mediator & mediator = this->mediator;
	LoopTimerManager & loop_timer = mediator.loop_timer;
	ComponentManager & mgr = mediator.component_manager;
	float dt = loop_timer.get_scaled_fixed_delta_time().count();

	RefVector<ParticleEmitter> emitters = mgr.get_components_by_type<ParticleEmitter>();

	for (ParticleEmitter & emitter : emitters) {
		// Get transform linked to emitter
		const Transform & transform
			= mgr.get_components_by_id<Transform>(emitter.game_object_id).front().get();

		// Emit particles based on emission_rate
		emitter.spawn_accumulator = emitter.data.emission_rate * dt;
		while (emitter.spawn_accumulator >= 1.0) {
			this->emit_particle(emitter, transform);
			emitter.spawn_accumulator -= 1.0;
    }
		
		// Update all particles
		for (Particle & particle : emitter.particles) {
			if (particle.active) {
				particle.update(dt);
			}
		}

		// Check if within boundary
		this->check_bounds(emitter, transform);
	}
}

void ParticleSystem::emit_particle(ParticleEmitter & emitter, const Transform & transform) {
	constexpr float DEG_TO_RAD = M_PI / 180.0;

	vec2 initial_position = emitter.data.position + transform.position;
	float random_angle = this->generate_random_angle(emitter.data.min_angle, emitter.data.max_angle);

	float random_speed = this->generate_random_speed(emitter.data.min_speed, emitter.data.max_speed);
	float angle_radians = random_angle * DEG_TO_RAD;

	vec2 velocity
		= {random_speed * std::cos(angle_radians), random_speed * std::sin(angle_radians)};

	for (Particle & particle : emitter.particles) {
		if (!particle.active) {
			particle.reset(emitter.data.end_lifespan, initial_position, velocity,
						   random_angle);
			break;
		}
	}
}

void ParticleSystem::check_bounds(ParticleEmitter & emitter, const Transform & transform) {
	vec2 offset = emitter.data.boundary.offset + transform.position + emitter.data.position;
	float half_width = emitter.data.boundary.width / 2.0;
	float half_height = emitter.data.boundary.height / 2.0;

	float left = offset.x - half_width;
	float right = offset.x + half_width;
	float top = offset.y - half_height;
	float bottom = offset.y + half_height;

	for (Particle & particle : emitter.particles) {
		const vec2 & position = particle.position;
		bool within_bounds = (position.x >= left && position.x <= right && position.y >= top
							  && position.y <= bottom);
		//if not within bounds do a reset or stop velocity
		if (!within_bounds) {
			if (emitter.data.boundary.reset_on_exit) {
				particle.active = false;
			} else {
				particle.velocity = {0, 0};
				if (position.x < left) particle.position.x = left;
				else if (position.x > right) particle.position.x = right;
				if (position.y < top) particle.position.y = top;
				else if (position.y > bottom) particle.position.y = bottom;
			}
		}
	}
}

float ParticleSystem::generate_random_angle(float min_angle, float max_angle) const {
	if (min_angle == max_angle) {
		return min_angle;
	} else if (min_angle < max_angle) {
		return min_angle
			   + static_cast<float>(std::rand() % static_cast<int>(max_angle - min_angle));
	} else {
		float angle_offset = (360 - min_angle) + max_angle;
		float random_angle
			= min_angle + static_cast<float>(std::rand() % static_cast<int>(angle_offset));
		return (random_angle >= 360) ? random_angle - 360 : random_angle;
	}
}

float ParticleSystem::generate_random_speed(float min_speed, float max_speed) const {
	if (min_speed == max_speed) {
		return min_speed;
	} else {
		return min_speed
			   + static_cast<float>(std::rand() % static_cast<int>(max_speed - min_speed));
	}
}
