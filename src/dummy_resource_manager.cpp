



#include "api/game.h"
#include "api/resource_manager.h"
#include "api/spritesheet.h"
#include "facade/Texture.h"
#include "util/log.h"
#include <vector>

using namespace crepe;

int main(){


	dbg_trace();

	// get instance of resource manager
	//api::ResourceManager& c_ResMan = api::ResourceManager::get_instance();

	
	game engine;

	api::ResourceManager& c_ResMan = api::ResourceManager::get_instance();

	auto test = c_ResMan.Load<Texture>("../asset/texture/img.png");

	auto img = Texture("../asset/texture/img.png");

	auto SS  = api::Spritesheet("../asset/spritesheet/spritesheet_test.png", 1 , 4);
	
	std::vector<Texture*> t = {test};
	std::vector<api::Spritesheet*> s = {&SS};

	engine.render(t, s);

}
