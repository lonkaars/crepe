


#include "renderSystem.h"
#include <vector>

#include "api/Color.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "facade/SdlContext.h"
#include "facade/Texture.h"

using namespace crepe::api;


static crepe::Texture player("../asset/texture/img.png");


void RenderSystem::render(){

	Sprite sprite(player, Color::get_red(), {1,1});
	Transform transform ={
		.position = {0,0},
		.rotation = 0,
		.scale = 1,
	};

	// this will get changed to ecs getter of componets
	crepe::SdlContext& ctx = crepe::SdlContext::get_instance();

	ctx.draw(sprite, transform);
	/*
	for(const auto& S : test_objects){
		ctx.draw(S, const api::Transform &)
	}
	*/
}
