#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>

#include "../api/Camera.h"
#include "../api/ParticleEmitter.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../facade/Texture.h"
#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "util/AbsoluutPosition.h"

#include "RenderSystem.h"
#include "types.h"

using namespace crepe;
using namespace std;

void RenderSystem::clear_screen() {
	SDLContext & ctx = this->mediator.sdl_context;
	ctx.clear_screen();
}

void RenderSystem::present_screen() {
	SDLContext & ctx = this->mediator.sdl_context;
	ctx.present_screen();
}

void RenderSystem::update_camera() {
	ComponentManager & mgr = this->mediator.component_manager;
	SDLContext & ctx = this->mediator.sdl_context;
	RefVector<Camera> cameras = mgr.get_components_by_type<Camera>();

	if (cameras.size() == 0) throw std::runtime_error("No cameras in current scene");

	for (Camera & cam : cameras) {
		if (!cam.active) continue;
		const Transform & transform
			= mgr.get_components_by_id<Transform>(cam.game_object_id).front().get();
		vec2 new_camera_pos = transform.position + cam.data.postion_offset;
		ctx.update_camera_view(cam, new_camera_pos);
		return;
	}
	throw std::runtime_error("No active cameras in current scene");
}

bool sorting_comparison(const Sprite & a, const Sprite & b) {
	if (a.data.sorting_in_layer != b.data.sorting_in_layer)
		return a.data.sorting_in_layer < b.data.sorting_in_layer;
	if (a.data.order_in_layer != b.data.order_in_layer)
		return a.data.order_in_layer < b.data.order_in_layer;

	return false;
}

RefVector<Sprite> RenderSystem::sort(RefVector<Sprite> & objs) const {
	RefVector<Sprite> sorted_objs(objs);
	std::sort(sorted_objs.begin(), sorted_objs.end(), sorting_comparison);

	return sorted_objs;
}

void RenderSystem::update() {
	this->clear_screen();
	this->render();
	this->present_screen();
}

bool RenderSystem::render_particle(const Sprite & sprite, const double & scale) {

	ComponentManager & mgr = this->mediator.component_manager;
	SDLContext & ctx = this->mediator.sdl_context;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	Texture & res = resource_manager.get<Texture>(sprite.source);

	vector<reference_wrapper<ParticleEmitter>> emitters
		= mgr.get_components_by_id<ParticleEmitter>(sprite.game_object_id);

	bool rendering_particles = false;

	for (const ParticleEmitter & em : emitters) {
		if (&em.data.sprite != &sprite) continue;
		rendering_particles = true;
		if (!em.active) continue;

		for (const Particle & p : em.data.particles) {
			if (!p.active) continue;

			ctx.draw(SDLContext::RenderContext{
				.sprite = sprite,
				.texture = res,
				.pos = p.position,
				.angle = p.angle,
				.scale = scale,
			});
		}
	}
	return rendering_particles;
}
void RenderSystem::render_normal(const Sprite & sprite, const Transform & tm) {
	SDLContext & ctx = this->mediator.sdl_context;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	const Texture & res = resource_manager.get<Texture>(sprite.source);
	vec2 pos = AbsoluutPosition::get_position(tm,sprite.data.position_offset);
	ctx.draw(SDLContext::RenderContext{
		.sprite = sprite,
		.texture = res,
		.pos = pos,
		.angle = tm.rotation,
		.scale = tm.scale,
	});
}

void RenderSystem::render() {
	ComponentManager & mgr = this->mediator.component_manager;
	this->update_camera();

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
