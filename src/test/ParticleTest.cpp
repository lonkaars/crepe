#include "api/Asset.h"
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/LoopTimerManager.h>
#include <gtest/gtest.h>
#include <math.h>
#define protected public
#define private public
#include <crepe/Particle.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/system/ParticleSystem.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class ParticlesTest : public ::testing::Test {
	Mediator m;

public:
	ComponentManager component_manager{m};
	ParticleSystem particle_system{m};
	LoopTimerManager loop_timer{m};

	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
		std::vector<std::reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			GameObject game_object = mgr.new_object("", "", vec2{0, 0}, 0, 0);

			Color color(0, 0, 0, 0);
			auto s1 = Asset("asset/texture/img.png");
			Sprite & test_sprite = game_object.add_component<Sprite>(
				s1, Sprite::Data{
						.color = color,
						.flip = Sprite::FlipSettings{true, true},
						.size = {10, 10},
					});

			game_object.add_component<ParticleEmitter>(test_sprite,
													   ParticleEmitter::Data{
														   .position = {0, 0},
														   .max_particles = 100,
														   .emission_rate = 0,
														   .min_speed = 0,
														   .max_speed = 0,
														   .min_angle = 0,
														   .max_angle = 0,
														   .begin_lifespan = 0,
														   .end_lifespan = 0,
														   .force_over_time = vec2{0, 0},
														   .boundary{
															   .width = 0,
															   .height = 0,
															   .offset = vec2{0, 0},
															   .reset_on_exit = false,
														   },
													   });
		}
		transforms = mgr.get_components_by_id<Transform>(0);
		Transform & transform = transforms.front().get();
		transform.position.x = 0.0;
		transform.position.y = 0.0;
		transform.rotation = 0.0;
		std::vector<std::reference_wrapper<ParticleEmitter>> rigidbodies
			= mgr.get_components_by_id<ParticleEmitter>(0);
		ParticleEmitter & emitter = rigidbodies.front().get();
		emitter.data.position = {0, 0};
		emitter.data.emission_rate = 0;
		emitter.data.min_speed = 0;
		emitter.data.max_speed = 0;
		emitter.data.min_angle = 0;
		emitter.data.max_angle = 0;
		emitter.data.begin_lifespan = 0;
		emitter.data.end_lifespan = 0;
		emitter.data.force_over_time = vec2{0, 0};
		emitter.data.boundary = {0, 0, vec2{0, 0}, false};
		for (auto & particle : emitter.particles) {
			particle.active = false;
		}
	}
};

TEST_F(ParticlesTest, spawnParticle) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 5;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.max_speed = 0.1;
	emitter.data.max_angle = 0.1;
	emitter.data.max_speed = 10;
	emitter.data.max_angle = 10;
	particle_system.update();
	//check if nothing happend
	EXPECT_EQ(emitter.particles[0].active, false);
	emitter.data.emission_rate = 50;
	//check particle spawnes
	particle_system.update();
	EXPECT_EQ(emitter.particles[0].active, true);
	particle_system.update();
	EXPECT_EQ(emitter.particles[1].active, true);
	particle_system.update();
	EXPECT_EQ(emitter.particles[2].active, true);
	particle_system.update();
	EXPECT_EQ(emitter.particles[3].active, true);

	for (auto & particle : emitter.particles) {
		// Check velocity range
		EXPECT_GE(particle.velocity.x, emitter.data.min_speed);
		// Speed should be greater than or equal to min_speed
		EXPECT_LE(particle.velocity.x, emitter.data.max_speed);
		// Speed should be less than or equal to max_speed
		EXPECT_GE(particle.velocity.y, emitter.data.min_speed);
		// Speed should be greater than or equal to min_speed
		EXPECT_LE(particle.velocity.y, emitter.data.max_speed);
		// Speed should be less than or equal to max_speed

		// Check angle range
		EXPECT_GE(particle.angle, emitter.data.min_angle);
		// Angle should be greater than or equal to min_angle
		EXPECT_LE(particle.angle, emitter.data.max_angle);
		// Angle should be less than or equal to max_angle
	}
}

TEST_F(ParticlesTest, moveParticleHorizontal) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.min_speed = 50;
	emitter.data.max_speed = 50;
	emitter.data.max_angle = 0;
	emitter.data.emission_rate = 50;
	for (int a = 1; a < emitter.data.boundary.width / 2; a++) {
		particle_system.update();
		EXPECT_EQ(emitter.particles[0].position.x, a);
	}
}

TEST_F(ParticlesTest, moveParticleVertical) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.min_speed = 50;
	emitter.data.max_speed = 50;
	emitter.data.min_angle = 90;
	emitter.data.max_angle = 90;
	emitter.data.emission_rate = 50;
	for (int a = 1; a < emitter.data.boundary.width / 2; a++) {
		particle_system.update();
		EXPECT_EQ(emitter.particles[0].position.y, a);
	}
}

TEST_F(ParticlesTest, boundaryParticleReset) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 10;
	emitter.data.boundary.width = 10;
	emitter.data.boundary.reset_on_exit = true;
	emitter.data.min_speed = 1;
	emitter.data.max_speed = 1;
	emitter.data.min_angle = 90;
	emitter.data.max_angle = 90;
	emitter.data.emission_rate = 1;
	for (int a = 0; a < emitter.data.boundary.width / 2 + 1; a++) {
		particle_system.update();
	}
	EXPECT_EQ(emitter.particles[0].active, false);
}

TEST_F(ParticlesTest, boundaryParticleStop) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 10;
	emitter.data.boundary.width = 10;
	emitter.data.boundary.reset_on_exit = false;
	emitter.data.min_speed = 1;
	emitter.data.max_speed = 1;
	emitter.data.min_angle = 90;
	emitter.data.max_angle = 90;
	emitter.data.emission_rate = 1;
	for (int a = 0; a < emitter.data.boundary.width / 2 + 1; a++) {
		particle_system.update();
	}
	const double TOLERANCE = 0.01;
	EXPECT_NEAR(emitter.particles[0].velocity.x, 0, TOLERANCE);
	EXPECT_NEAR(emitter.particles[0].velocity.y, 0, TOLERANCE);
	if (emitter.particles[0].velocity.x != 0)
		EXPECT_NEAR(std::abs(emitter.particles[0].position.x),
					emitter.data.boundary.height / 2, TOLERANCE);
	if (emitter.particles[0].velocity.y != 0)
		EXPECT_NEAR(std::abs(emitter.particles[0].position.y), emitter.data.boundary.width / 2,
					TOLERANCE);
}
