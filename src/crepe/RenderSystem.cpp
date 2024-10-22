

#include "RenderSystem.h"
#include "ComponentManager.h"
#include "SdlContext.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "util/log.h"
#include <cstddef>
#include <functional>
#include <vector>

using namespace crepe;
using namespace crepe::api;

RenderSystem::RenderSystem() { dbg_trace(); }

RenderSystem::~RenderSystem() { dbg_trace(); }

RenderSystem& RenderSystem::get_instance(){
	static RenderSystem instance;
	return instance;
}

void RenderSystem::update() {

	ComponentManager& mgr = ComponentManager::get_instance();
	
	std::vector<std::reference_wrapper<Sprite>> sprites = mgr.get_components_by_type<Sprite>();
	std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_type<Transform>();

	SdlContext& render = SdlContext::get_instance();
	render.clear_screen();

	for (size_t i = 0; i < sprites.size(); ++i) {
			render.draw(sprites[i].get(), transforms[i].get());
	}

	render.present_screen();

}
