#include "api/LoopTimer.h"
#include "SDLContext.h"
namespace crepe::api {
LoopTimer::LoopTimer() {}

LoopTimer & LoopTimer::getInstance() {
	static LoopTimer instance;
	return instance;
}

void LoopTimer::start() {
	last_frame_time = SDLContext::get_instance().get_ticks();
    elapsed_time = 0;
    elapsed_fixed_time = 0;
    delta_time = 0;
}

void LoopTimer::update() {
	uint64_t currentFrameTime = SDLContext::get_instance().get_ticks();
	delta_time = (currentFrameTime - last_frame_time) / 1000.0;

	if (delta_time > maximum_delta_time) {
		delta_time = maximum_delta_time;
	}
	delta_time *= game_scale;
	elapsed_time += delta_time;
	last_frame_time = currentFrameTime;
}

double LoopTimer::get_delta_time() const { return delta_time; }
int LoopTimer::get_current_time() const { return elapsed_time; }

void LoopTimer::advance_fixed_update() { elapsed_fixed_time += fixed_delta_time; }

double LoopTimer::get_fixed_delta_time() const { return fixed_delta_time; }

void LoopTimer::set_fps(int fps) {
	this->fps = fps;
	frame_target_time = 1.0 / fps;
}

int LoopTimer::get_fps() const { return fps; }
void LoopTimer::set_game_scale(double value) { game_scale = value; };
double LoopTimer::get_game_scale() const { return game_scale; }
void LoopTimer::enforce_frame_rate() {
	uint64_t currentFrameTime = SDLContext::get_instance().get_ticks();
	double frameDuration = (currentFrameTime - last_frame_time) / 1000.0;

	if (frameDuration < frame_target_time) {
		uint32_t delayTime
			= (uint32_t) ((frame_target_time - frameDuration) * 1000.0);
		SDLContext::get_instance().delay(delayTime);
	}
}
double LoopTimer::get_lag() const { return elapsed_time - elapsed_fixed_time; }

} // namespace crepe::api
