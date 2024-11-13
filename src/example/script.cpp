/** \file
 * 
 * Standalone example for usage of the script component and system
 */

#include <crepe/ComponentManager.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>

using namespace crepe;
using namespace std;

// Unrelated stuff that is not part of this POC
int _ = []() {
	// Show dbg_trace() output
	auto & cfg = Config::get_instance();
	cfg.log.level = LogLevel::TRACE;

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
	ComponentManager component_manager{};
	ScriptSystem system{component_manager};

	// Create game object with Transform and BehaviorScript components
	auto & obj = component_manager.new_object("name");
	obj.add_component<BehaviorScript>().set_script<MyScript>();

	// Update all scripts. This should result in MyScript::update being called
	system.update();

	return EXIT_SUCCESS;
}
