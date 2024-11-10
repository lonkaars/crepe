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
				.max_particles = 1,
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
		std::vector<std::reference_wrapper<Rigidbody>> rigidbodies
			= mgr.get_components_by_id<Rigidbody>(0);
		Rigidbody & rigidbody = rigidbodies.front().get();
		rigidbody.data.angular_velocity = 0;
		rigidbody.data.linear_velocity.x = 0;
		rigidbody.data.linear_velocity.y = 0;
	}
};

TEST_F(ParticlesTest, spawnParticle) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	ParticleEmitter & emitter = mgr.get_components_by_id<ParticleEmitter>(0).front().get();
	emitter.data.end_lifespan = 5;
	emitter.data.boundary.height = 100;
	emitter.data.boundary.width = 100;
	emitter.data.max_speed = 1;
	emitter.data.max_angle = 1;
	particle_system.update(); 
	//check if nothing happend
	EXPECT_EQ(emitter.data.particles.size(), 0);
	emitter.data.emission_rate = 1;
	particle_system.update();
	//check if particle spawned
	EXPECT_EQ(emitter.data.particles.size(), 1);
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
