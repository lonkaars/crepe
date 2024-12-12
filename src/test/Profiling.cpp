#include <chrono>
#include <cmath>
#include <crepe/api/Asset.h>
#include <crepe/manager/Mediator.h>
#include <crepe/manager/ResourceManager.h>
#include <crepe/system/ParticleSystem.h>
#include <crepe/system/PhysicsSystem.h>
#include <crepe/system/RenderSystem.h>
#include <gtest/gtest.h>

#define private public
#define protected public

#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>
#include <crepe/facade/SDLContext.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/EventManager.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/types.h>
#include <crepe/util/Log.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;
using namespace testing;

class TestScript : public Script {
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.this_collider.game_object_id);
		return true;
	}
	void init() {
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->oncollision(ev); });
	}
	void fixed_update() {
		// Retrieve component from the same GameObject this script is on
	}
};

class DISABLED_ProfilingTest : public Test {
public:
	// Config for test
	// Minimum amount to let test pass
	const int min_gameobject_count = 100;
	// Maximum amount to stop test
	const int max_gameobject_count = 150;
	// Amount of times a test runs to calculate average
	const int average = 5;
	// Maximum duration to stop test
	const std::chrono::microseconds duration = 16000us;

	Mediator m;
	SDLContext sdl_context{m};
	ResourceManager resman{m};
	ComponentManager mgr{m};
	// Add system used for profling tests
	CollisionSystem collision_sys{m};
	PhysicsSystem physics_sys{m};
	ParticleSystem particle_sys{m};
	RenderSystem render_sys{m};
	ScriptSystem script_sys{m};

	// Test data
	std::map<std::string, std::chrono::microseconds> timings;
	int game_object_count = 0;
	std::chrono::microseconds total_time = 0us;

	void SetUp() override {

		GameObject do_not_use = mgr.new_object("DO_NOT_USE", "", {0, 0});
		do_not_use.add_component<Camera>(ivec2{1080, 720}, vec2{2000, 2000},
										 Camera::Data{
											 .bg_color = Color::WHITE,
											 .zoom = 1.0f,
										 });
		// initialize systems here:
		//calls init
		script_sys.fixed_update();
		//creates window
		render_sys.frame_update();
	}

	// Helper function to time an update call and store its duration
	template <typename Func>
	std::chrono::microseconds time_function(const std::string & name, Func && func) {
		auto start = std::chrono::steady_clock::now();
		func();
		auto end = std::chrono::steady_clock::now();
		std::chrono::microseconds duration
			= std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		timings[name] += duration;
		return duration;
	}

	// Run and profile all systems, return the total time in milliseconds
	std::chrono::microseconds run_all_systems() {
		std::chrono::microseconds total_microseconds = 0us;
		total_microseconds += time_function("PhysicsSystem", [&]() { physics_sys.fixed_update(); });
		total_microseconds
			+= time_function("CollisionSystem", [&]() { collision_sys.fixed_update(); });
		total_microseconds
			+= time_function("ParticleSystem", [&]() { particle_sys.fixed_update(); });
		total_microseconds += time_function("RenderSystem", [&]() { render_sys.frame_update(); });
		return total_microseconds;
	}

	// Print timings of all functions
	void log_timings() const {
		std::string result = "\nFunction timings:\n";

		for (const auto & [name, duration] : timings) {
			result += name + " took " + std::to_string(duration.count() / 1000.0 / average)
					  + " ms (" + std::to_string(duration.count() / average) + " µs).\n";
		}

		result += "Total time: " + std::to_string(this->total_time.count() / 1000.0 / average)
				  + " ms (" + std::to_string(this->total_time.count() / average) + " µs)\n";

		result += "Amount of gameobjects: " + std::to_string(game_object_count) + "\n";

		GTEST_LOG_(INFO) << result;
	}

	void clear_timings() {
		for (auto & [key, value] : timings) {
			value = std::chrono::microseconds(0);
		}
	}
};

TEST_F(DISABLED_ProfilingTest, Profiling_1) {
	while (this->total_time / this->average < this->duration) {

		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object("gameobject", "", {0, 0});
		}

		this->game_object_count++;

		this->total_time = 0us;
		clear_timings();

		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if (this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}

TEST_F(DISABLED_ProfilingTest, Profiling_2) {
	while (this->total_time / this->average < this->duration) {

		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object(
				"gameobject", "", {static_cast<float>(game_object_count * 2), 0});
			gameobject.add_component<Rigidbody>(Rigidbody::Data{
				.gravity_scale = 0.0,
				.body_type = Rigidbody::BodyType::STATIC,
			});
			gameobject.add_component<BoxCollider>(vec2{0, 0}, vec2{1, 1});

			gameobject.add_component<BehaviorScript>().set_script<TestScript>();
			Sprite & test_sprite = gameobject.add_component<Sprite>(
				Asset{"asset/texture/square.png"},
				Sprite::Data{
					.color = {0, 0, 0, 0},
					.flip = {.flip_x = false, .flip_y = false},
					.sorting_in_layer = 1,
					.order_in_layer = 1,
					.size = {.y = 500},
				});
		}

		this->game_object_count++;

		this->total_time = 0us;
		clear_timings();
		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if (this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}

TEST_F(DISABLED_ProfilingTest, Profiling_3) {
	while (this->total_time / this->average < this->duration) {

		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object(
				"gameobject", "", {static_cast<float>(game_object_count * 2), 0});
			gameobject.add_component<Rigidbody>(Rigidbody::Data{
				.gravity_scale = 0,
				.body_type = Rigidbody::BodyType::STATIC,
			});
			gameobject.add_component<BoxCollider>(vec2{0, 0}, vec2{1, 1});
			gameobject.add_component<BehaviorScript>().set_script<TestScript>();
			Sprite & test_sprite = gameobject.add_component<Sprite>(
				Asset{"asset/texture/square.png"},
				Sprite::Data{
					.color = {0, 0, 0, 0},
					.flip = {.flip_x = false, .flip_y = false},
					.sorting_in_layer = 1,
					.order_in_layer = 1,
					.size = {.y = 500},
				});
			auto & test = gameobject.add_component<ParticleEmitter>(ParticleEmitter::Data{
				.max_particles = 10,
				.emission_rate = 100,
				.end_lifespan = 100000,
				.boundary{
					.width = 1000,
					.height = 1000,
					.offset = vec2{0, 0},
					.reset_on_exit = false,
				},
				.sprite = test_sprite,
			});
		}
		render_sys.frame_update();
		this->game_object_count++;

		this->total_time = 0us;
		clear_timings();
		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if (this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}
