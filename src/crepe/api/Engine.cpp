#include "../util/Log.h"

#include "Engine.h"

using namespace crepe;
using namespace std;

void Engine::start() {
	try {
		this->setup();
	} catch (const exception & e) {
		Log::logf(Log::Level::ERROR, "Uncaught exception in setup: {}\n", e.what());
		return;
	}

	try {
		this->loop();
	} catch (const exception & e) {
		Log::logf(Log::Level::ERROR, "Uncaught exception in main loop: {}\n", e.what());
		this->event_manager.trigger_event<ShutDownEvent>();
	}
}

void Engine::setup() {
	this->game_running = true;
	this->loop_timer.start();
	this->scene_manager.load_next_scene();

	this->event_manager.subscribe<ShutDownEvent>([this](const ShutDownEvent & event) {
		this->game_running = false;

		// propagate to possible user ShutDownEvent listeners
		return false;
	});
}

void Engine::loop() {
	LoopTimerManager & timer = this->loop_timer;
	SystemManager & systems = this->system_manager;

	while (game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			try {
				systems.fixed_update();
			} catch (const exception & e) {
				Log::logf(Log::Level::WARNING, "Uncaught exception in fixed update function: {}\n", e.what());
			}
			timer.advance_fixed_elapsed_time();
		}

		try {
			systems.frame_update();
		} catch (const exception & e) {
			Log::logf(Log::Level::WARNING, "Uncaught exception in frame update function: {}\n", e.what());
		}
		timer.enforce_frame_rate();
	}
}

