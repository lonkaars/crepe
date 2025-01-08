#include <crepe/api/BehaviorScript.h>

#include "ZapperPoolScript.h"
#include "ZapperPoolSubScene.h"

using namespace crepe;
using namespace std;

ZapperPoolSubScene::ZapperPoolSubScene(Scene & scene)
	: controller {scene.new_object("controller")} {

	vector<ZapperObject> pool;
	for (size_t i = 0; i < this->POOL_SIZE; i++)
		pool.emplace_back(scene.new_object("zapper", "zapper"));
	BehaviorScript & behavior = this->controller.add_component<BehaviorScript>();
	behavior.set_script<ZapperPoolScript>(std::move(pool));
}
