#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"

#include "RenderSystem.h"

using namespace crepe;

void RenderSystem::clear_screen() const { SDLContext::get_instance().clear_screen(); }

void RenderSystem::present_screen() const { SDLContext::get_instance().present_screen(); }
void RenderSystem::update_camera() {
	ComponentManager & mgr = this->component_manager;

	std::vector<std::reference_wrapper<Camera>> cameras = mgr.get_components_by_type<Camera>();

	for (Camera & cam : cameras) {
		SDLContext::get_instance().camera(cam);
		this->curr_cam = &cam;
	}
}

bool sorting_comparison(const Sprite & a, const Sprite & b) {
	if (a.sorting_in_layer > b.sorting_in_layer) return true;
	if (a.sorting_in_layer == b.sorting_in_layer) return a.order_in_layer > b.order_in_layer;

	return false;
}

std::vector<std::reference_wrapper<Sprite>>
RenderSystem::sort(std::vector<std::reference_wrapper<Sprite>> & objs) {
	if (objs.empty()) return {};

	std::vector<std::reference_wrapper<Sprite>> sorted_objs(objs);
	std::sort(sorted_objs.begin(), sorted_objs.end(), sorting_comparison);

	return sorted_objs;
}

void RenderSystem::render_sprites() {
	ComponentManager & mgr = this->component_manager;

	auto sprites = mgr.get_components_by_type<Sprite>();
	auto sorted_sprites = this->sort(sprites);

	SDLContext & render = SDLContext::get_instance();
	for (const Sprite & sprite : sorted_sprites) {
		auto transforms = mgr.get_components_by_id<Transform>(sprite.game_object_id);
		render.draw(sprite, transforms[0], *curr_cam);
	}
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render_sprites();
	this->present_screen();
}
