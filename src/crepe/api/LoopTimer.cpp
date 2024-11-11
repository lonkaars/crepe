
#include "../facade/SDLContext.h"
#include "../util/log.h"

#include "LoopTimer.h"

using namespace crepe;

LoopTimer::LoopTimer() { dbg_trace(); }

LoopTimer & LoopTimer::get_instance() {
	static LoopTimer instance;
	return instance;
}

void LoopTimer::start() {
	this->last_frame_time = SDLContext::get_instance().get_ticks();
	this->elapsed_time = 0;
	this->elapsed_fixed_time = 0;
	this->delta_time = 0;
}

void LoopTimer::update() {
	uint64_t current_frame_time = SDLContext::get_instance().get_ticks();
	this->delta_time = (current_frame_time - last_frame_time);

	if (this->delta_time > this->maximum_delta_time) {
		this->delta_time = this->maximum_delta_time;
	}
	this->delta_time *= this->game_scale;
	this->elapsed_time += this->delta_time;
	this->last_frame_time = current_frame_time;
}

double LoopTimer::get_delta_time() const { return this->delta_time; }
double LoopTimer::get_current_time() const { return this->elapsed_time; }
void LoopTimer::advance_fixed_update() {
	this->elapsed_fixed_time += this->fixed_delta_time;
}
double LoopTimer::get_fixed_delta_time() const {
	return this->fixed_delta_time;
}

void LoopTimer::set_fps(int fps) {
	this->fps = fps;
	//! use fps to calculate frame_target_time in ms
	this->frame_target_time = 1000.0 / this->fps;
}

int LoopTimer::get_fps() const { return this->fps; }
void LoopTimer::set_game_scale(double value) { this->game_scale = value; }
double LoopTimer::get_game_scale() const { return this->game_scale; }

void LoopTimer::enforce_frame_rate() {
	uint64_t current_frame_time = SDLContext::get_instance().get_ticks();
	double frame_duration = (current_frame_time - this->last_frame_time);

	if (frame_duration < this->frame_target_time) {
		uint32_t delay_time
			= static_cast<uint32_t>(this->frame_target_time - frame_duration);
		SDLContext::get_instance().delay(delay_time);
	}

	this->last_frame_time = current_frame_time;
}

double LoopTimer::get_lag() const {
	return this->elapsed_time - this->elapsed_fixed_time;
}
