#include "../facade/SDLContext.h"
#include "../manager/EventManager.h"
#include "../system/AnimatorSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/InputSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"
#include "../manager/EventManager.h"
#include "../util/Log.h"

#include "LoopManager.h"

using namespace crepe;
using namespace std;

LoopManager::LoopManager() {
	this->load_system<AnimatorSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<RenderSystem>();
	this->load_system<ScriptSystem>();
	this->load_system<InputSystem>();
	this->event_manager.subscribe<ShutDownEvent>(
		[this](const ShutDownEvent & event) { return this->on_shutdown(event); });
}
void LoopManager::start() {
	this->setup();
	this->loop();
}

void LoopManager::setup() {
	this->game_running = true;
	this->loop_timer.start();
	this->scene_manager.load_next_scene();
}

void LoopManager::loop() {
	try {

	while (game_running) {
		this->loop_timer.update();

		while (this->loop_timer.get_lag() >= this->loop_timer.get_fixed_delta_time()) {
			this->fixed_update();
			this->loop_timer.advance_fixed_elapsed_time();
		}

		this->frame_update();
		this->loop_timer.enforce_frame_rate();
	}
	}catch(const exception & e){
		Log::logf(Log::Level::ERROR, "Exception caught in main loop: %s", e.what());
		this->event_manager.trigger_event<ShutDownEvent>(ShutDownEvent{});
	}
}

// will be called at a fixed interval
void LoopManager::fixed_update() {
	this->get_system<InputSystem>().update();
	this->event_manager.dispatch_events();
	this->get_system<ScriptSystem>().update();
	this->get_system<PhysicsSystem>().update();
	this->get_system<CollisionSystem>().update();
}

// will be called every frame
void LoopManager::frame_update() { 
	this->scene_manager.load_next_scene();
	this->get_system<AnimatorSystem>().update();
	//render
	this->get_system<RenderSystem>().update();
}

bool LoopManager::on_shutdown(const ShutDownEvent & e) {
	this->game_running = false;
	// propagate to possible user ShutDownEvent listeners
	return false;
}
