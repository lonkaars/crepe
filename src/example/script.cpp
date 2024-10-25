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

class MyScript : public Script {
	void update() {
		Transform & test = get_component<Transform>();
		dbg_logf("Transform(%.2f, %.2f)", test.position.x, test.position.y);
	}
};

int main() {
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::LogLevel::TRACE;

	auto obj = GameObject(0, "name", "tag", 0);
	Point point = {
		.x = 1.2,
		.y = 3.4,
	};
	obj.add_component<Transform>(point, 0, 0);
	obj.add_component<BehaviorScript>().set_script<MyScript>();

	auto & sys = ScriptSystem::get_instance();
	sys.update(); // -> MyScript::update

	return 0;
}
