/** \file
 * 
 * Standalone example for usage of the internal ECS
 */

#include <cassert>
#include <chrono>

#include <crepe/Collider.h>
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>
#include <crepe/Rigidbody.h>
#include <crepe/Sprite.h>
#include <crepe/util/log.h>

using namespace crepe;
using namespace std;

#define OBJ_COUNT 100000

int main() {
	dbg_trace();

	auto & mgr = ComponentManager::get_instance();

	auto start_adding = chrono::high_resolution_clock::now();

	GameObject * game_object[OBJ_COUNT];

	for (int i = 0; i < OBJ_COUNT; ++i) {
		game_object[i] = new GameObject(i, "Name", "Tag", 0);

		game_object[i]->add_component<Sprite>("test");
		game_object[i]->add_component<Rigidbody>(0, 0, i);
		game_object[i]->add_component<Collider>(i);
	}

	auto stop_adding = chrono::high_resolution_clock::now();

	auto sprites = mgr.get_components_by_type<Sprite>();
	for (auto sprite : sprites) {
		assert(sprite.get().path == "test");
	}

	auto stop_looping = chrono::high_resolution_clock::now();

	for (int i = 0; i < OBJ_COUNT; ++i) {
		delete game_object[i];
	}

	auto add_time = chrono::duration_cast<chrono::microseconds>(stop_adding
																- start_adding);
	auto loop_time = chrono::duration_cast<chrono::microseconds>(stop_looping
																 - stop_adding);
	printf("add time:  %ldus\n", add_time.count());
	printf("loop time: %ldus\n", loop_time.count());

	return 0;
}
