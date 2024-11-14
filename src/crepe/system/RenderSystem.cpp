#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../util/log.h"
#include "Asset.h"

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

std::vector<std::reference_wrapper<Sprite>>
RenderSystem::sort(std::vector<std::reference_wrapper<Sprite>> & objs) {
	if (objs.empty()) return {};

	std::vector<std::reference_wrapper<Sprite>> sorted_objs;
	sorted_objs.insert(sorted_objs.end(), objs.begin(), objs.end());
	assert(sorted_objs.size() != objs.size());

	std::sort(sorted_objs.begin(), sorted_objs.end(),
			  [](const std::reference_wrapper<Sprite> & a,
				 const std::reference_wrapper<Sprite> & b) {
				  const Sprite & sprite_a = a.get();
				  const Sprite & sprite_b = b.get();
				  if (sprite_a.sorting_in_layer == sprite_b.sorting_in_layer) {
					  return sprite_a.order_in_layer < sprite_b.order_in_layer;
				  }
				  return sprite_a.sorting_in_layer < sprite_b.sorting_in_layer;
			  });
	return sorted_objs;
}

void RenderSystem::render_sprites() {

	ComponentManager & mgr = ComponentManager::get_instance();

	auto sprites = mgr.get_components_by_type<Sprite>();

	auto sorted_sprites = this->sort(sprites);
	
	SDLContext & render = SDLContext::get_instance();
	for (const Sprite & sprite : sorted_sprites) {
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
