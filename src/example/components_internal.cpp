/** \file
 * 
 * Standalone example for usage of the internal ECS
 */

#include <cassert>
#include <chrono>

#include <crepe/Component.h>
#include <crepe/ComponentManager.h>

#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>

#include <crepe/util/Log.h>

using namespace crepe;
using namespace std;

#define OBJ_COUNT 100000

int main() {
	dbg_trace();

	ComponentManager mgr{};

	auto start_adding = chrono::high_resolution_clock::now();

	for (int i = 0; i < OBJ_COUNT; ++i) {
		GameObject obj = mgr.new_object("Name", "Tag");
		obj.add_component<Sprite>("test");
		obj.add_component<Rigidbody>(0, 0, i);
	}

	auto stop_adding = chrono::high_resolution_clock::now();

	auto sprites = mgr.get_components_by_type<Sprite>();
	for (auto sprite : sprites) {
		assert(true);
	}

	auto stop_looping = chrono::high_resolution_clock::now();

	auto add_time = chrono::duration_cast<chrono::microseconds>(stop_adding - start_adding);
	auto loop_time = chrono::duration_cast<chrono::microseconds>(stop_looping - stop_adding);
	printf("add time:  %ldus\n", add_time.count());
	printf("loop time: %ldus\n", loop_time.count());

	return 0;
}
