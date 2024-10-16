/** \file
 * 
 * Standalone example for usage of the script component and system
 */

#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>
#include <crepe/ScriptSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/BehaviorScript.h>

using namespace crepe;
using namespace std;

class MyScript : public api::BehaviorScript {
	void update() { dbg_trace(); }
};

int main() {
	dbg_trace();

	auto obj = GameObject(0, "name", "tag", 0);
	obj.add_component<MyScript>();

	auto & sys = ScriptSystem::get_instance();
	sys.update(); // -> MyScript::update

	return 0;
}
