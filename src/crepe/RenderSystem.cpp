

#include "RenderSystem.h"
#include "ComponentManager.h"
#include "SdlContext.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "util/log.h"
#include <functional>
#include <vector>

using namespace crepe;
using namespace crepe::api;

RenderSystem::RenderSystem() { dbg_trace(); }

RenderSystem::~RenderSystem() { dbg_trace(); }

RenderSystem & RenderSystem::get_instance() {
	static RenderSystem instance;
	return instance;
}

void RenderSystem::update() {

	ComponentManager & mgr = ComponentManager::get_instance();

	std::vector<std::reference_wrapper<Sprite>> sprites
		= mgr.get_components_by_type<Sprite>();

	SdlContext & render = SdlContext::get_instance();
	render.clear_screen();

	for (const Sprite & sprite : sprites) {
		std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(sprite.gameObjectId);
		for (const Transform& transform : transforms) {
			render.draw(sprite, transform);
		}

	}
	render.present_screen();
}
