
#include "../facade/SDLContext.h"

#include "LoopTimer.h"


using namespace crepe;
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
    uint64_t current_frame_time = SDLContext::get_instance().get_ticks();
    delta_time = (current_frame_time - last_frame_time) / 1000.0;

    if (delta_time > maximum_delta_time) {
        delta_time = maximum_delta_time;
    }
    delta_time = game_scale;
    elapsed_time += delta_time;
    last_frame_time = current_frame_time;
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
    uint64_t current_frame_time = SDLContext::get_instance().get_ticks();
    double frame_duration = (current_frame_time - last_frame_time) / 1000.0;

    if (frame_duration < frame_target_time) {
        uint32_t delay_time
            = (uint32_t) ((frame_target_time - frame_duration) / 1000.0);
        SDLContext::get_instance().delay(delay_time);
    }
}
double LoopTimer::get_lag() const { return elapsed_time - elapsed_fixed_time; }
