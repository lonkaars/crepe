#include <cmath>
#include <ctime>
#include <cstdlib>

#include "api/ParticleEmitter.h"
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

		//	Get transform linked to emitter
		const Transform& transform = mgr.get_components_by_id<Transform>(emitter.GAME_OBJECT_ID).front().get();

		//	Check if within boundary
		check_bounds(emitter,transform);
		
		// Emit particles based on emission_rate
		int updates = calculate_update(this->update_count,emitter.data.emission_rate);
		for (size_t i = 0; i < updates; i++)
		{
			emit_particle(emitter,transform);		
		}
		
		// Update all particles
		for (size_t j = 0; j < emitter.data.particles.size(); j++) {
			if (emitter.data.particles[j].active) {
				emitter.data.particles[j].update();
			}
		}
	}
	update_count++;
	if(update_count == MAX_UPDATE_COUNT) update_count = 0;
}

void ParticleSystem::emit_particle(ParticleEmitter & emitter,const Transform& transform) {
	constexpr double DEG_TO_RAD = M_PI / 180.0;

	Vector2 initial_position = emitter.data.position + transform.position;
	double min_angle = emitter.data.min_angle;
	double max_angle = emitter.data.max_angle;
	double random_angle;
	
	if (min_angle <= max_angle) {
			// Standard range (e.g., 10 to 20 degrees)
			double angle_offset = max_angle - min_angle;
			random_angle = min_angle + static_cast<double>(std::rand() % static_cast<uint32_t>(angle_offset));
	} else {
			// Wrap-around range (e.g., 350 to 10 degrees)
			double angle_offset = (360 - min_angle) + max_angle;
			random_angle = min_angle + static_cast<double>(std::rand() % static_cast<uint32_t>(angle_offset));
			
			// Wrap around to keep random_angle within 0-360 degrees
			if (random_angle >= 360) {
					random_angle -= 360;
			}
	}

	// Generate a random speed between min_speed and max_speed
	double speed_offset = emitter.data.max_speed - emitter.data.min_speed;
	double random_speed = emitter.data.min_speed + static_cast<double>(std::rand() % static_cast<uint32_t>(speed_offset));

	// Convert random_angle to radians
	double angle_radians = random_angle * DEG_TO_RAD;

	Vector2 velocity = {
        random_speed * std::cos(angle_radians),
        random_speed * std::sin(angle_radians)
    };


	for (size_t i = 0; i < emitter.data.particles.size(); i++) {
		if (!emitter.data.particles[i].active) {
			emitter.data.particles[i].reset(emitter.data.end_lifespan, initial_position,velocity,random_angle);
			break;
		}
	}
}

int ParticleSystem::calculate_update(int count, double emission) {

		//get interger part of the emission
		double integer_part = std::floor(emission);

    // Get the fractional part of the emission
    double fractional_part = emission - integer_part;

    // Convert the fractional part to a denominator value
    int denominator = static_cast<int>(1.0 / fractional_part);

    // For emissions like 0.01, 0.1, 0.5, etc., calculate the update frequency
    if (fractional_part > 0) {
			// Calculate how often the update should be triggered based on the fractional part
			if (count % denominator == 0) {
				return 1;
			} else {
				return 0;
			}
    }
		
    // For integer emissions, return the emission directly
    return static_cast<int>(emission);
}

void ParticleSystem::check_bounds(ParticleEmitter & emitter,const Transform& transform)
{
		Vector2 offset = emitter.data.boundary.boundary_offset + transform.position + emitter.data.position;
		double half_width = emitter.data.boundary.boundary_width / 2.0;
		double half_height = emitter.data.boundary.boundary_height / 2.0;

		// Define boundary edges
		const double left = offset.x - half_width;
		const double right = offset.x + half_width;
		const double top = offset.y - half_height;
		const double bottom = offset.y + half_height;

		std::vector<Particle>& particles = emitter.data.particles;
		for (Particle& particle : particles)
		{
				const Vector2& position = particle.position;

				// Check if particle is within bounds
				bool within_bounds = (position.x >= left && position.x <= right && position.y >= top && position.y <= bottom);
				if (!within_bounds)
				{
						if (emitter.data.boundary.reset_on_exit)
						{
								particle.active = false;
						}
						else
						{
								particle.velocity = {0, 0};
								//todo add that particle goes back to boundary
						}
				}
		}
}
