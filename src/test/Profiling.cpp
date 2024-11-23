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
#include <crepe/system/CollisionSystem.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/types.h>
#include <crepe/util/Log.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;
using namespace testing;

class TestScript : public Script {
	bool oncollision(const CollisionEvent& test) {
		Log::logf("Box {} script on_collision()", test.info.first.collider.game_object_id);
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
	ComponentManager mgr;
	// Add system used for profling tests 
	CollisionSystem collision_sys{mgr};
	PhysicsSystem physics_sys{mgr};
	ParticleSystem particle_sys{mgr};
	RenderSystem render_sys{mgr};
	ScriptSystem script_sys{mgr};

	// Store individual function timings
	std::map<std::string, long long> timings; 

	// Min and max gameobject that should and can be created
	int min_gameobject_count = 100;
	int max_gameobject_count = 1000;
	
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
	long long time_function(const std::string& name, Func&& func) {
		auto start = std::chrono::steady_clock::now();
		func();
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		timings[name] = duration; // Store the duration in microseconds
		return duration; // Return the duration in microseconds
	}

	// Run and profile all systems, return the total time in milliseconds
	long long run_all_systems() {
		long long total_microseconds = 0;
		total_microseconds += time_function("PhysicsSystem", [&]() { physics_sys.update(); });
		total_microseconds += time_function("CollisionSystem", [&]() { collision_sys.update(); });
		total_microseconds += time_function("ParticleSystem", [&]() { particle_sys.update(); });
		total_microseconds += time_function("RenderSystem", [&]() { render_sys.update(); });
		return total_microseconds;
	}

	// Print timings of all functions
	void log_timings(long long total_time,int game_object_count) const {
		std::stringstream ss;
		ss <<  std::endl <<"Function timings:\n";  // Starting with a header
		for (const auto& [name, duration] : timings) {
				ss << name << " took " << duration / 1000.0 << " ms (" << duration << " µs). " << std::endl;
		}
		ss << "Total time: " << total_time / 1000.0  << "ms (" << total_time  << " µs)" << std::endl;
		ss << "Amount of gameobjects: " << game_object_count << std::endl;
		// Use GTest INFO macro to print the accumulated log without extra newlines
		GTEST_LOG_(INFO) << ss.str();
	}
};

TEST_F(Profiling, Profiling_example) {
	int game_object_count = 0;
	long long total_time = 0;
	while (total_time < 16000) {
		
		{
			//define gameobject used for testing
			GameObject gameobject = mgr.new_object("gameobject","",{0,0});
		}

		game_object_count++;
		total_time = run_all_systems();
		if(game_object_count >= max_gameobject_count) break;
	}
	log_timings(total_time,game_object_count);
	EXPECT_GE(game_object_count, min_gameobject_count);
}

TEST_F(Profiling, Profiling_small_object_no_collision) {
	int game_object_count = 0;
	long long total_time = 0;
	while (total_time < 16000) {
	
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
			make_shared<Texture>("/home/jaro/crepe/asset/texture/green_square.png"), color,
			FlipSettings{true, true});
		}
		
		render_sys.update();
		game_object_count++;
		total_time = run_all_systems();
		if(game_object_count >= max_gameobject_count) break;
	}
	log_timings(total_time,game_object_count);
	EXPECT_GE(game_object_count, min_gameobject_count);
}
