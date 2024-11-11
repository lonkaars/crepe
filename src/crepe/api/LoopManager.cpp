
#include "../facade/SDLContext.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"

#include "LoopManager.h"
#include "LoopTimer.h"

using namespace crepe;

LoopManager::LoopManager(
	const RenderSystem & renderSystem, const SDLContext & sdlContext,
	const LoopTimer & loopTimer, const ScriptSystem & scriptSystem,
	const SoundSystem & soundSystem, const ParticleSystem & particleSystem,
	const PhysicsSystem & physicsSystem, const AnimatorSystem & animatorSystem,
	const CollisionSystem & collisionSystem) {
	// Initialize systems if needed
	// Example: this->renderSystem = renderSystem;
}
void LoopManager::process_input() {
	SDLContext::get_instance().handle_events(this->game_running);
}
void LoopManager::start() {
	this->setup();
	this->loop();
}
void LoopManager::set_running(bool running) { this->game_running = running; }

void LoopManager::fixed_update() {}

void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::get_instance();
	timer.start();

	while (game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			this->process_input();
			this->fixed_update();
			timer.advance_fixed_update();
		}

		this->update();
		this->render();

		timer.enforce_frame_rate();
	}
}

void LoopManager::setup() {
	this->game_running = true;
	LoopTimer::get_instance().start();
	LoopTimer::get_instance().set_fps(60);
}

void LoopManager::render() {
	if (this->game_running) {
		RenderSystem::get_instance().update();
	}
}

void LoopManager::update() { LoopTimer & timer = LoopTimer::get_instance(); }
