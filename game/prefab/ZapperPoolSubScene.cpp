#include <crepe/api/BehaviorScript.h>

#include "ZapperPoolSubScene.h"
#include "ZapperPoolScript.h"

using namespace crepe;
using namespace std;

ZapperPoolSubScene::ZapperPoolSubScene(Scene & scene)
	: controller { scene.new_object("controller") } {

	Log::logf(Log::DEBUG, "Building zapper pool...");
	vector<ZapperObject> pool;
	for (size_t i = 0; i < this->POOL_SIZE; i++)
		pool.emplace_back(scene.new_object("zapper", "zapper"));
	BehaviorScript & behavior = this->controller.add_component<BehaviorScript>();
	behavior.set_script<ZapperPoolScript>(std::move(pool));
}

