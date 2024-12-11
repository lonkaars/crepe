#include "Engine.h"

using namespace crepe;
using namespace std;

void Engine::start() {
	this->setup();
	this->loop();
}

void Engine::setup() {
	LoopTimer & timer = this->loop_timer;
	this->game_running = true;
	this->scene_manager.load_next_scene();
	timer.start();
	timer.set_fps(200);
}

void Engine::loop() {
	LoopTimer & timer = this->loop_timer;
	SystemManager & systems = this->system_manager;

	timer.start();

	while (game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			systems.fixed_update();
			timer.advance_fixed_update();
		}

		systems.frame_update();
		timer.enforce_frame_rate();
	}
}

