#include <cmath>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../api/ParticleEmitter.h"
#include "../api/Vector2.h"

#include "RenderSystem.h"

using namespace crepe;

void RenderSystem::clear_screen() const { SDLContext::get_instance().clear_screen(); }

void RenderSystem::present_screen() const { SDLContext::get_instance().present_screen(); }
void RenderSystem::update_camera() {
	ComponentManager & mgr = this->component_manager;

	auto cameras = mgr.get_components_by_type<Camera>();

	for (Camera & cam : cameras) {
		SDLContext::get_instance().camera(cam);
		this->curr_cam = &cam;
	}
}

bool RenderSystem::render_particle(const Sprite & sprite,
								   const double & scale) {

	ComponentManager & mgr = this->component_manager;
	SDLContext & render = SDLContext::get_instance();

	auto emitters = mgr.get_components_by_id<ParticleEmitter>(sprite.game_object_id);

	bool rendering_particles = false;

	for (const ParticleEmitter & em : emitters) {
		if (!em.active) continue;
		if (!(em.data.sprite.game_object_id == sprite.game_object_id)) continue;

		rendering_particles = true;

		for (const Particle & p : em.data.particles) {
			if (!p.active) continue;
			render.draw_particle(sprite, p.position, p.angle, scale, *this->curr_cam);
		}
	}
	return rendering_particles;
}
void RenderSystem::render_normal(const Sprite & sprite, const Transform & tm) {

	ComponentManager & mgr = this->component_manager;
	SDLContext & render = SDLContext::get_instance();
	
	render.draw(sprite, tm, *curr_cam);
}

void RenderSystem::render() {

	ComponentManager & mgr = this->component_manager;

	auto sprites = mgr.get_components_by_type<Sprite>();
	for (const Sprite & sprite : sprites) {
		if (!sprite.active) continue;
		auto transform = mgr.get_components_by_id<Transform>(sprite.game_object_id).front().get();

		bool rendered_particles = this->render_particle(sprite, transform.scale);

		if (rendered_particles) continue;

		this->render_normal(sprite, transform);
	}
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render();
	this->present_screen();
}
