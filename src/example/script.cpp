/** \file
 * 
 * Standalone example for usage of the script component and system
 */

#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>
#include <crepe/ScriptSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/Config.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Script.h>

using namespace crepe;
using namespace crepe::api;
using namespace std;

class MyScript : public Script {
	void update() { dbg_log("MY SCRIPT UPDATE"); }
};

int main() {
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::log_level::TRACE;

	auto obj = GameObject(0, "name", "tag", 0);
	obj.add_component<BehaviorScript>().set_script<MyScript>();

	auto & sys = ScriptSystem::get_instance();
	sys.update(); // -> MyScript::update

	return 0;
}
