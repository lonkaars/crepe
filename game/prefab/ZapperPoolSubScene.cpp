#include <crepe/api/BehaviorScript.h>

#include "ZapperPoolSubScene.h"
#include "ZapperPoolScript.h"

using namespace crepe;
using namespace std;

ZapperPoolSubScene::ZapperPoolSubScene(Scene & scene)
	: controller { scene.new_object("controller") } {
	this->controller.add_component<BehaviorScript>().set_script<ZapperPoolScript>(*this);

	Log::logf(Log::DEBUG, "Building zapper pool...");
	for (size_t i = 0; i < this->POOL_SIZE; i++)
		zappers.emplace_back(scene.new_object("zapper"));
}

OptionalRef<ZapperObject> ZapperPoolSubScene::get_next_zapper() {
	for (ZapperObject & zapper : this->zappers) {
		if (!zapper.active) continue;
		return zapper;
	}
	return {};
}

