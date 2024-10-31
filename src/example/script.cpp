/** \file
 * 
 * Standalone example for usage of the script component and system
 */

#include <crepe/ComponentManager.h>
#include <crepe/ScriptSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>

using namespace crepe;
using namespace crepe::api;
using namespace std;

// Unrelated stuff that is not part of this POC
int _ = [] () {
	// Show dbg_trace() output
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::LogLevel::TRACE;

	return 0; // satisfy compiler
}();



// User-defined script:
class MyScript : public Script {
	void update() {
		// Retrieve component from the same GameObject this script is on
		Transform & test = get_component<Transform>();
		dbg_logf("Transform(%.2f, %.2f)", test.position.x, test.position.y);
	}
};

int main() {
	// Create game object with Transform and BehaviorScript components
	auto obj = GameObject(0, "name", "tag", 0);
	obj.add_component<Transform>(Point { .x = 1.2, .y = 3.4, }, 0, 0);
	obj.add_component<BehaviorScript>().set_script<MyScript>();

	// Get ScriptSystem singleton instance (this would normally be done from the
	// game loop)
	auto & sys = ScriptSystem::get_instance();
	// Update all scripts. This should result in MyScript::update being called
	sys.update();

	return EXIT_SUCCESS;
}

