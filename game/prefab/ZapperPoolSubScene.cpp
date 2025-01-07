#include "ZapperPoolSubScene.h"

using namespace crepe;
using namespace std;

ZapperPoolSubScene::ZapperPoolSubScene(Scene & scene)
	: controller { scene.new_object("controller") } {
		for (size_t i = 0; i < this->POOL_SIZE; i++)
			zappers.emplace_back(scene.new_object("zapper"));

	
}

