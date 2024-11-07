#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../util/log.h"

#include "RenderSystem.h"

using namespace crepe;

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

	SDLContext & render = SDLContext::get_instance();
	render.clear_screen();

	for (const Sprite & sprite : sprites) {
		std::vector<std::reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(sprite.GAME_OBJECT_ID);
		for (const Transform & transform : transforms) {
			render.draw(sprite, transform);
		}
	}
	render.present_screen();
}
