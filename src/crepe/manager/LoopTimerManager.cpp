#include <chrono>
#include <thread>

#include "../util/Log.h"

#include "LoopTimerManager.h"

using namespace crepe;
using namespace std::chrono;
using namespace std::chrono_literals;

LoopTimerManager::LoopTimerManager(Mediator & mediator) : Manager(mediator) {
	this->mediator.loop_timer = *this;
	dbg_trace();
}

void LoopTimerManager::start() {
	this->last_frame_time = std::chrono::steady_clock::now();

	this->elapsed_time = elapsed_time_t{0};
	// by starting the elapsed_fixed_time at (0 - fixed_delta_time) in milliseconds it calls a fixed update at the start of the loop.
	// this->elapsed_fixed_time = -this->fixed_delta_time;
	this->delta_time = duration_t{0};
}

void LoopTimerManager::update() {
	TimePoint_t current_frame_time
		= std::chrono::steady_clock::now();
	// Convert to duration in seconds for delta time
	this->delta_time = current_frame_time - last_frame_time;

	if (this->delta_time > this->maximum_delta_time) {
		this->delta_time = this->maximum_delta_time;
	}
	if (this->delta_time > 0s) {
		this->actual_fps = 1.0 / duration_cast<seconds>(this->delta_time).count();
	} else {
		this->actual_fps = 0;
	}
	this->elapsed_time += duration_cast<elapsed_time_t>(this->delta_time);
	this->last_frame_time = current_frame_time;
}

Duration_t LoopTimerManager::get_delta_time() const {return this->delta_time * this->time_scale;}

elapsed_time_t LoopTimerManager::get_elapsed_time() const { return this->elapsed_time; }

void LoopTimerManager::advance_fixed_elapsed_time() {
	this->elapsed_fixed_time += std::chrono::duration_cast<ElapsedTime_t>(this->fixed_delta_time);
}

void LoopTimerManager::set_target_framerate(unsigned fps) {
	this->target_fps = fps;
	//check if fps is lower or equals 0
	if (fps <= 0) return;
	// target time per frame in seconds
	this->frame_target_time = duration_t(1s) / this->target_fps;
}

unsigned LoopTimerManager::get_fps() const { return this->actual_fps; }

void LoopTimerManager::set_time_scale(double value) { this->time_scale = value; }

float LoopTimerManager::get_time_scale() const { return this->time_scale; }

void LoopTimerManager::enforce_frame_rate() {
	TimePoint_t current_frame_time
		= std::chrono::steady_clock::now();
	Duration_t frame_duration = current_frame_time - this->last_frame_time;
	// Check if frame duration is less than the target frame time
	if (frame_duration < this->frame_target_time) {
		duration_t delay_time = this->frame_target_time - frame_duration;
		if (delay_time > 0s) {
			std::this_thread::sleep_for(delay_time);
		}
	}
}

duration_t LoopTimerManager::get_lag() const {
	return this->elapsed_time - this->elapsed_fixed_time;
}

duration_t LoopTimerManager::get_scaled_fixed_delta_time() const {
	return this->fixed_delta_time * this->time_scale;
}

void LoopTimerManager::set_fixed_delta_time(float seconds) {
	this->fixed_delta_time = duration_t(seconds);
}

Duration_t LoopTimerManager::get_fixed_delta_time() const {
	return this->fixed_delta_time;
}
