#include "../util/Log.h"

#include "Engine.h"

using namespace crepe;
using namespace std;

int Engine::main() noexcept {
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
	SystemManager & systems = this->system_manager;

	while (this->game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			try {
				systems.fixed_update();
			} catch (const exception & e) {
				Log::logf(Log::Level::WARNING,
						  "Uncaught exception in fixed update function: {}\n", e.what());
			}
			timer.advance_fixed_elapsed_time();
		}

		try {
			systems.frame_update();
			this->scene_manager.load_next_scene();
		} catch (const exception & e) {
			Log::logf(Log::Level::WARNING, "Uncaught exception in frame update function: {}\n",
					  e.what());
		}
		timer.enforce_frame_rate();
	}
}
