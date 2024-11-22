#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "../ComponentManager.h"
#include "../api/ParticleEmitter.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../api/Vector2.h"
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
		if (!cam.active) continue;
		this->context.set_camera(cam, this->scale);
		this->curr_cam_ref = &cam;
	}
}

bool sorting_comparison(const Sprite & a, const Sprite & b) {
	if (a.sorting_in_layer < b.sorting_in_layer) return true;
	if (a.sorting_in_layer == b.sorting_in_layer) return a.order_in_layer < b.order_in_layer;

	return false;
}

RefVector<Sprite> RenderSystem::sort(RefVector<Sprite> & objs) const {
	RefVector<Sprite> sorted_objs(objs);
	std::sort(sorted_objs.begin(), sorted_objs.end(), sorting_comparison);

	return sorted_objs;
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render();
	this->present_screen();
}

bool RenderSystem::render_particle(const Sprite & sprite, const double & scale) {

	ComponentManager & mgr = this->component_manager;

	vector<reference_wrapper<ParticleEmitter>> emitters
		= mgr.get_components_by_id<ParticleEmitter>(sprite.game_object_id);

	bool rendering_particles = false;

	for (const ParticleEmitter & em : emitters) {
		if (!(&em.data.sprite == &sprite)) continue;
		rendering_particles = true;
		if (!em.active) continue;

		for (const Particle & p : em.data.particles) {
			if (!p.active) continue;
			this->context.draw_particle(sprite, p.position ,p.angle, this->curr_cam_ref->pos ,scale, this->scale);
		}
	}
	return rendering_particles;
}
void RenderSystem::render_normal(const Sprite & sprite, const Transform & tm) {
	this->context.draw(sprite, tm , this->curr_cam_ref->pos,this->scale);
}

void RenderSystem::render() {

	ComponentManager & mgr = this->component_manager;
	RefVector<Sprite> sprites = mgr.get_components_by_type<Sprite>();
	RefVector<Sprite> sorted_sprites = this->sort(sprites);

	for (const Sprite & sprite : sorted_sprites) {
		if (!sprite.active) continue;
		const Transform & transform
			= mgr.get_components_by_id<Transform>(sprite.game_object_id).front().get();

		bool rendered_particles = this->render_particle(sprite, transform.scale);

		if (rendered_particles) continue;

		this->render_normal(sprite, transform);
	}
}
