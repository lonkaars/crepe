#include <segvcatch.h>

#include "../facade/SignalCatch.h"
#include "../util/Log.h"

#include "Engine.h"

using namespace crepe;
using namespace std;

int Engine::main() noexcept {
	SignalCatch signal_catch;

	try {
		this->setup();
	} catch (const exception & e) {
		Log::logf(Log::Level::ERROR, "Uncaught exception in setup: {}\n", e.what());
		return EXIT_FAILURE;
	}

	try {
		this->loop();
	} catch (const exception & e) {
		Log::logf(Log::Level::ERROR, "Uncaught exception in main loop: {}\n", e.what());
		this->event_manager.trigger_event<ShutDownEvent>();
	}

	return EXIT_SUCCESS;
}

void Engine::setup() {
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

	while (this->game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			try {
				this->fixed_update();
			} catch (const exception & e) {
				Log::logf(
					Log::Level::WARNING, "Uncaught exception in fixed update function: {}",
					e.what()
				);
			}
		}

		try {
			this->frame_update();
		} catch (const exception & e) {
			Log::logf(
				Log::Level::WARNING, "Uncaught exception in frame update function: {}",
				e.what()
			);
		}
	}
}

void Engine::fixed_update() {
	this->system_manager.fixed_update();
	this->loop_timer.advance_fixed_elapsed_time();
}

void Engine::frame_update() {
	this->system_manager.frame_update();
	this->loop_timer.enforce_frame_rate();
}
