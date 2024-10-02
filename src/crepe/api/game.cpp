


#include "game.h"
#include "api/spritesheet.h"
#include "facade/SdlContext.h"
#include "facade/Texture.h"
#include <vector>


void game::render(std::vector<crepe::Texture*> & draw, std::vector<crepe::api::Spritesheet*> & ss){
	auto& ctx = crepe::SdlContext::get_instance();

	ctx.loop(*draw[0], *ss[0]);
}



