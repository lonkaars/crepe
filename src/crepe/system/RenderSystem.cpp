#include <cmath>
#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../util/log.h"
#include "Particle.h"
#include "api/ParticleEmitter.h"
#include "api/Vector2.h"

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


void RenderSystem::render_particle(const ParticleEmitter& em, Transform & tm){
	if (!em.active) return;
	
	SDLContext & render = SDLContext::get_instance();
	for (const Particle& p  : em.data.particles) {
		if (!p.active) continue;
		tm.position = p.position;
		tm.rotation = p.angle;
		render.draw(em.data.sprite, tm , *curr_cam);
	}
}
void RenderSystem::render_sprites() {

	ComponentManager & mgr = ComponentManager::get_instance();

	auto emitter = mgr.get_components_by_type<ParticleEmitter>();

	SDLContext & render = SDLContext::get_instance();
	Transform test(1, Vector2{0,0},0,0);

	for (const ParticleEmitter & em : emitter) {
		auto transforms
			= mgr.get_components_by_id<Transform>(em.game_object_id);
		test.scale = transforms[0].get().scale;
		this->render_particle(em, test);
	}
}

void RenderSystem::update() {
	this->clear_screen();
	this->update_camera();
	this->render_sprites();
	this->present_screen();
}
