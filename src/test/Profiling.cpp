#include "system/ParticleSystem.h"
#include "system/PhysicsSystem.h"
#include "system/RenderSystem.h"
#include <cmath>
#include <chrono>
#include <gtest/gtest.h>

#define private public
#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/types.h>
#include <crepe/util/Log.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;
using namespace testing;


/*
List of test cases with component settings/details
1. Minimal test creates gameobject without additonal components
2. Minimal 'Complex' gameobject. Has dynamic body without bounce and no collision handler
3. Minimal 'Complex' gameobject. Same as test 2 but with particle emitter
*/

class TestScript : public Script {
	bool oncollision(const CollisionEvent& test) {
		Log::logf("Box {} script on_collision()", test.info.first_collider.game_object_id);
		return true;
	}
	void init() {
		subscribe<CollisionEvent>([this](const CollisionEvent& ev) -> bool {
			return this->oncollision(ev);
		});
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
	}
};

class Profiling : public Test {
public:
	// Config for test
	// Minimum amount to let test pass
	const int min_gameobject_count = 100;
	// Maximum amount to stop test
	const int max_gameobject_count = 200;
	// Amount of times a test runs to calculate average
	const int average = 5;
	// Maximum duration to stop test
	const std::chrono::microseconds duration = 16000us;
	

	ComponentManager mgr;
	// Add system used for profling tests 
	CollisionSystem collision_sys{mgr};
	PhysicsSystem physics_sys{mgr};
	ParticleSystem particle_sys{mgr};
	RenderSystem render_sys{mgr};
	ScriptSystem script_sys{mgr};

	// Test data
	std::map<std::string, std::chrono::microseconds> timings;
	int game_object_count = 0;
	std::chrono::microseconds total_time = 0us;

	
	void SetUp() override {
		
		GameObject do_not_use = mgr.new_object("DO_NOT_USE","",{0,0});
		do_not_use.add_component<Camera>(Color::WHITE);
		// initialize systems here:
		//calls init
		script_sys.update();
		//creates window
		render_sys.update();
	}

	// Helper function to time an update call and store its duration
	template <typename Func>
	std::chrono::microseconds time_function(const std::string& name, Func&& func) {
		auto start = std::chrono::steady_clock::now();
		func();
		auto end = std::chrono::steady_clock::now();
		std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		timings[name] += duration;
		return duration;
	}

	// Run and profile all systems, return the total time in milliseconds
	std::chrono::microseconds run_all_systems() {
		std::chrono::microseconds total_microseconds = 0us;
		total_microseconds += time_function("PhysicsSystem", [&]() { physics_sys.update(); });
		total_microseconds += time_function("CollisionSystem", [&]() { collision_sys.update(); });
		total_microseconds += time_function("ParticleSystem", [&]() { particle_sys.update(); });
		total_microseconds += time_function("RenderSystem", [&]() { render_sys.update(); });
		return total_microseconds;
	}

	// Print timings of all functions
	void log_timings() const {
		std::stringstream ss;
        ss << "\nFunction timings:\n";
        for (const auto& [name, duration] : timings) {
            ss << name << " took " << duration.count() / 1000.0 / average << " ms (" << duration.count() / average << " µs).\n";
        }
        ss << "Total time: " << this->total_time.count() / 1000.0 / average << " ms (" << this->total_time.count() / average << " µs)\n";
        ss << "Amount of gameobjects: " << game_object_count << "\n";
        GTEST_LOG_(INFO) << ss.str();
	}

	void clear_timings() {
		for (auto& [key, value] : timings) {
    	value = std::chrono::microseconds(0);
		}
	}
};

TEST_F(Profiling, Profiling_1) {
	while (this->total_time/this->average < this->duration) {
		

		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object("gameobject","",{0,0});
		}

		this->game_object_count++;

		this->total_time = 0us;
		clear_timings();

		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if(this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}

TEST_F(Profiling, Profiling_2) {
	while (this->total_time/this->average < this->duration) {
	
		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object("gameobject","",{static_cast<float>(game_object_count*2),0});
			gameobject.add_component<Rigidbody>(Rigidbody::Data{
			.body_type = Rigidbody::BodyType::STATIC,
			.use_gravity = false,
			});
			gameobject.add_component<BoxCollider>(vec2{0, 0}, 1, 1);
			gameobject.add_component<BehaviorScript>().set_script<TestScript>();
			Color color(0, 0, 0, 0);
			gameobject.add_component<Sprite>(
			make_shared<Texture>("asset/texture/green_square.png"), color,
			FlipSettings{true, true});
		}

		this->game_object_count++;

		this->total_time = 0us;
		clear_timings();
		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if(this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}

TEST_F(Profiling, Profiling_3) {
	while (this->total_time/this->average < this->duration) {
	
		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object("gameobject","",{static_cast<float>(game_object_count*2),0});
			gameobject.add_component<Rigidbody>(Rigidbody::Data{
			.body_type = Rigidbody::BodyType::STATIC,
			.use_gravity = false,
			});
			gameobject.add_component<BoxCollider>(vec2{0, 0}, 1, 1);
			gameobject.add_component<BehaviorScript>().set_script<TestScript>();
			Color color(0, 0, 0, 0);
			gameobject.add_component<Sprite>(
			make_shared<Texture>("asset/texture/green_square.png"), color,
			FlipSettings{true, true});
			Sprite & test_sprite = gameobject.add_component<Sprite>(
			make_shared<Texture>("asset/texture/img.png"), color, FlipSettings{false, false});
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
		render_sys.update();
		this->game_object_count++;
		
		this->total_time = 0us;
		clear_timings();
		for (int amount = 0; amount < this->average; amount++) {
			this->total_time += run_all_systems();
		}

		if(this->game_object_count >= this->max_gameobject_count) break;
	}
	log_timings();
	EXPECT_GE(this->game_object_count, this->min_gameobject_count);
}
