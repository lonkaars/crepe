#include <chrono>
#include <thread>

#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "LoopTimer.h"

using namespace crepe;

LoopTimer::LoopTimer() { dbg_trace(); }

void LoopTimer::start() {
	this->last_frame_time = std::chrono::steady_clock::now();

	this->elapsed_time = std::chrono::milliseconds(0);
	// by starting the elapsed_fixed_time at (0 - fixed_delta_time) in milliseconds it calls a fixed update at the start of the loop.
	this->elapsed_fixed_time
		= -std::chrono::duration_cast<std::chrono::milliseconds>(fixed_delta_time);
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
	this->actual_fps = 1.0 / this->delta_time.count();

	this->delta_time *= this->game_scale;
	this->elapsed_time += this->delta_time;
	this->last_frame_time = current_frame_time;
}

double LoopTimer::get_delta_time() const { return this->delta_time.count(); }

double LoopTimer::get_current_time() const { return this->elapsed_time.count(); }

void LoopTimer::advance_fixed_update() { this->elapsed_fixed_time += this->fixed_delta_time; }

double LoopTimer::get_fixed_delta_time() const { return this->fixed_delta_time.count(); }

void LoopTimer::set_target_fps(int fps) {
	this->target_fps = fps;
	// target time per frame in seconds
	this->frame_target_time = std::chrono::duration<double>(1.0) / this->target_fps;
}

int LoopTimer::get_fps() const { return this->actual_fps; }

void LoopTimer::set_game_scale(double value) { this->game_scale = value; }

double LoopTimer::get_game_scale() const { return this->game_scale; }
void LoopTimer::enforce_frame_rate() {
	auto current_frame_time = std::chrono::steady_clock::now();
	auto frame_duration = current_frame_time - this->last_frame_time;

	// Check if frame duration is less than the target frame time
	if (frame_duration < this->frame_target_time) {
		auto delay_time = std::chrono::duration_cast<std::chrono::microseconds>(
			this->frame_target_time - frame_duration);

		if (delay_time.count() > 0) {
			std::this_thread::sleep_for(delay_time);
		}
	}
}

double LoopTimer::get_lag() const {
	return (this->elapsed_time - this->elapsed_fixed_time).count();
}
