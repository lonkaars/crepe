#include <chrono>

#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "LoopTimer.h"

using namespace crepe;

LoopTimer::LoopTimer() { dbg_trace(); }

LoopTimer & LoopTimer::get_instance() {
	static LoopTimer instance;
	return instance;
}

void LoopTimer::start() {
	this->last_frame_time = std::chrono::steady_clock::now();
	this->elapsed_time = std::chrono::milliseconds(0);
	this->elapsed_fixed_time = std::chrono::milliseconds(0);
	this->delta_time = std::chrono::milliseconds(0);
}

void LoopTimer::update() {
	auto current_frame_time = std::chrono::steady_clock::now();
	// Convert to duration in seconds for delta time
	this->delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(
		current_frame_time - last_frame_time);

	if (this->delta_time > this->maximum_delta_time) {
		this->delta_time = this->maximum_delta_time;
	}

	this->delta_time *= this->game_scale;
	this->elapsed_time += this->delta_time;
	this->last_frame_time = current_frame_time;
}

double LoopTimer::get_delta_time() const { return this->delta_time.count(); }

double LoopTimer::get_current_time() const { return this->elapsed_time.count(); }

void LoopTimer::advance_fixed_update() { this->elapsed_fixed_time += this->fixed_delta_time; }

double LoopTimer::get_fixed_delta_time() const { return this->fixed_delta_time.count(); }

void LoopTimer::set_fps(int fps) {
	this->fps = fps;
	// target time per frame in seconds
	this->frame_target_time = std::chrono::duration<double>(1.0) / fps;
}

int LoopTimer::get_fps() const { return this->fps; }

void LoopTimer::set_game_scale(double value) { this->game_scale = value; }

double LoopTimer::get_game_scale() const { return this->game_scale; }
void LoopTimer::enforce_frame_rate() {
	std::chrono::steady_clock::time_point current_frame_time
		= std::chrono::steady_clock::now();
	std::chrono::milliseconds frame_duration
		= std::chrono::duration_cast<std::chrono::milliseconds>(current_frame_time
																- this->last_frame_time);

	if (frame_duration < this->frame_target_time) {
		std::chrono::milliseconds delay_time
			= std::chrono::duration_cast<std::chrono::milliseconds>(this->frame_target_time
																	- frame_duration);
		if (delay_time.count() > 0) {
			SDLContext::get_instance().delay(delay_time.count());
		}
	}

	this->last_frame_time = current_frame_time;
}

double LoopTimer::get_lag() const {
	return (this->elapsed_time - this->elapsed_fixed_time).count();
}
