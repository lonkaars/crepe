#include <math.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/system/ParticleSystem.h>
#include <gtest/gtest.h>


using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class ParticlesTest : public ::testing::Test {
protected:
	GameObject * game_object;
	ParticleSystem particle_system;
	void SetUp() override {
		ComponentManager & mgr = ComponentManager::get_instance();
		std::vector<std::reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			game_object = new GameObject(0, "", "", Vector2{0, 0}, 0, 0);
			game_object->add_component<ParticleEmitter>(ParticleEmitter::Data{
				.position = {0,0},
				.max_particles = 100,
				.emission_rate = 0,
				.min_speed = 0,
				.max_speed = 0,
				.min_angle = 0,
				.max_angle = 0,
				.begin_lifespan = 0,
				.end_lifespan = 0,
				.force_over_time = Vector2{0,0},
				.boundary{
					.width = 0,
					.height = 0,
					.offset = Vector2{0,0},
					.reset_on_exit = false,
				},
				.sprite = nullptr,
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
		emitter.data.force_over_time = Vector2{0, 0};
		emitter.data.boundary = {0, 0, Vector2{0, 0}, false};
		emitter.data.sprite = nullptr;
		for (auto& particle : emitter.data.particles) {
			particle.active = false;
		}
	}
};

TEST_F(ParticlesTest, spawnParticle) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
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
	EXPECT_EQ(emitter.data.particles[0].active, 0);
	emitter.data.emission_rate = 1;
	//check particle spawnes
	particle_system.update();
	EXPECT_EQ(emitter.data.particles[0].active, 1);
	particle_system.update();
	EXPECT_EQ(emitter.data.particles[1].active, 1);
	particle_system.update();
	EXPECT_EQ(emitter.data.particles[2].active, 1);
	particle_system.update();
	EXPECT_EQ(emitter.data.particles[3].active, 1);

	for (auto& particle : emitter.data.particles) {
        // Check velocity range
        EXPECT_GE(particle.velocity.x, emitter.data.min_speed);  // Speed should be greater than or equal to min_speed
        EXPECT_LE(particle.velocity.x, emitter.data.max_speed);  // Speed should be less than or equal to max_speed
		EXPECT_GE(particle.velocity.y, emitter.data.min_speed);  // Speed should be greater than or equal to min_speed
        EXPECT_LE(particle.velocity.y, emitter.data.max_speed);  // Speed should be less than or equal to max_speed

        // Check angle range
        EXPECT_GE(particle.angle, emitter.data.min_angle);  // Angle should be greater than or equal to min_angle
        EXPECT_LE(particle.angle, emitter.data.max_angle);  // Angle should be less than or equal to max_angle
    }

}

TEST_F(ParticlesTest, moveParticleHorizontal) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.min_speed = 1;
	emitter.data.max_speed = 1;
	emitter.data.max_angle = 0;
	emitter.data.emission_rate = 1;
	for (int a = 1; a < emitter.data.boundary.width/2; a++) {
		particle_system.update(); 
		EXPECT_EQ(emitter.data.particles[0].position.x,a);
	}
}


TEST_F(ParticlesTest, moveParticleVertical) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 100;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.min_speed = 1;
	emitter.data.max_speed = 1;
	emitter.data.min_angle = 90;
	emitter.data.max_angle = 90;
	emitter.data.emission_rate = 1;
	for (int a = 1; a < emitter.data.boundary.width/2; a++) {
		particle_system.update(); 
		EXPECT_EQ(emitter.data.particles[0].position.y,a);
	}
}
