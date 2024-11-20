#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"

#include "RenderSystem.h"

using namespace crepe;
using namespace std;

void RenderSystem::clear_screen() { this->context.clear_screen(); }

void RenderSystem::present_screen() { this->context.present_screen(); }
void RenderSystem::update_camera() {
	ComponentManager & mgr = this->component_manager;

	RefVector<Camera> cameras = mgr.get_components_by_type<Camera>();

	if (cameras.size() == 0) throw std::runtime_error("No cameras in current scene");

	for (Camera & cam : cameras) {
		this->context.camera(cam);
		this->curr_cam_ref = &cam;
	}
}

bool sorting_comparison(const Sprite & a, const Sprite & b) {
	if (a.sorting_in_layer < b.sorting_in_layer) return true;
	if (a.sorting_in_layer == b.sorting_in_layer) return a.order_in_layer < b.order_in_layer;

	return false;
}

RefVector<Sprite> RenderSystem::sort(RefVector<Sprite> & objs) {
	RefVector<Sprite> sorted_objs(objs);
	std::sort(sorted_objs.begin(), sorted_objs.end(), sorting_comparison);

	return sorted_objs;
}

void RenderSystem::render_sprites() {
	ComponentManager & mgr = this->component_manager;
	RefVector<Sprite> sprites = mgr.get_components_by_type<Sprite>();
	RefVector<Sprite> sorted_sprites = this->sort(sprites);

	for (const Sprite & sprite : sorted_sprites) {
		auto transforms = mgr.get_components_by_id<Transform>(sprite.game_object_id);
		this->context.draw(sprite, transforms[0], *this->curr_cam_ref);
	}
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render_sprites();
	this->present_screen();
}
