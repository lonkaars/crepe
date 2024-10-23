#include "ParticleSystem.h"
#include "ComponentManager.h"
#include "Particle.h"
#include "api/ParticleEmitter.h"
#include <cmath>
#include <ctime>

using namespace crepe;

ParticleSystem::ParticleSystem()
	: m_elapsed_time(0.0f) {} // Initialize m_elapsedTime to 0

void ParticleSystem::update() {
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<ParticleEmitter>> emitters
		= mgr.get_components_by_type<ParticleEmitter>();
	float delta_time = 0.10;
	for (ParticleEmitter & emitter : emitters) {
		float update_amount = 1 / static_cast<float>(emitter.m_emission_rate);
		for (float i = 0; i < delta_time; i += update_amount) {
			emit_particle(emitter);
		}
		for (size_t j = 0; j < emitter.particles.size(); j++) {
			if (emitter.particles[j].active) {
				emitter.particles[j].update(delta_time);
			}
		}
	}
}

void ParticleSystem::emit_particle(ParticleEmitter & emitter) {
	Position initial_position = {emitter.m_position.x, emitter.m_position.y};
	float random_angle = 0.0f;
	if (emitter.m_max_angle < emitter.m_min_angle) {
		random_angle = ((emitter.m_min_angle
						+ (std::rand()
						   % (static_cast<uint32_t>(emitter.m_max_angle + 360
													- emitter.m_min_angle + 1))))
					   % 360);
	} else {
		random_angle = emitter.m_min_angle
					  + (std::rand()
						 % (static_cast<uint32_t>(emitter.m_max_angle
												  - emitter.m_min_angle + 1)));
	}
	float angle_in_radians = random_angle * (M_PI / 180.0f);
	float random_speed_offset = (static_cast<float>(std::rand()) / RAND_MAX)
								  * (2 * emitter.m_speed_offset)
							  - emitter.m_speed_offset;
	float velocity_x
		= (emitter.m_speed + random_speed_offset) * std::cos(angle_in_radians);
	float velocity_y
		= (emitter.m_speed + random_speed_offset) * std::sin(angle_in_radians);
	Position initial_velocity = {velocity_x, velocity_y};
	for (size_t i = 0; i < emitter.particles.size(); i++) {
		if (!emitter.particles[i].active) {
			emitter.particles[i].reset(emitter.m_end_lifespan, initial_position,
									   initial_velocity);
			break;
		}
	}
}
