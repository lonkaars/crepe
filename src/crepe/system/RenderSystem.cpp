#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "RenderSystem.h"

using namespace crepe;

RenderSystem::RenderSystem() { dbg_trace(); }

RenderSystem::~RenderSystem() { dbg_trace(); }

RenderSystem & RenderSystem::get_instance() {
	static RenderSystem instance;
	return instance;
}

void RenderSystem::clear_screen() const {
	SDLContext::get_instance().clear_screen();
}

void RenderSystem::present_screen() const {
	SDLContext::get_instance().present_screen();
}
void RenderSystem::update_camera() {
	ComponentManager & mgr = ComponentManager::get_instance();

	std::vector<std::reference_wrapper<Camera>> cameras
		= mgr.get_components_by_type<Camera>();

	for (Camera & cam : cameras) {
		SDLContext::get_instance().camera(cam);
		this->curr_cam = &cam;
	}
}
void RenderSystem::render_sprites() const {

	ComponentManager & mgr = ComponentManager::get_instance();

	std::vector<std::reference_wrapper<Sprite>> sprites
		= mgr.get_components_by_type<Sprite>();

	SDLContext & render = SDLContext::get_instance();
	for (const Sprite & sprite : sprites) {
		auto transforms
			= mgr.get_components_by_id<Transform>(sprite.game_object_id);
		render.draw(sprite, transforms[0], *curr_cam);
	}
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render_sprites();
	this->present_screen();
}
