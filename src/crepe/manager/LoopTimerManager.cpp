#include <chrono>
#include <thread>

#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "LoopTimerManager.h"

using namespace crepe;

LoopTimerManager::LoopTimerManager(Mediator & mediator) : Manager(mediator) {
	this->mediator.loop_timer = *this;
	dbg_trace();
}

void LoopTimerManager::start() {
	this->last_frame_time = std::chrono::steady_clock::now();

	this->elapsed_time = std::chrono::milliseconds(0);
	// by starting the elapsed_fixed_time at (0 - fixed_delta_time) in milliseconds it calls a fixed update at the start of the loop.
	this->elapsed_fixed_time
		= -std::chrono::duration_cast<std::chrono::milliseconds>(fixed_delta_time);
	this->delta_time = std::chrono::milliseconds(0);
}

void LoopTimerManager::update() {
	auto current_frame_time = std::chrono::steady_clock::now();
	// Convert to duration in seconds for delta time
	this->delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(
		current_frame_time - last_frame_time);

	if (this->delta_time > this->maximum_delta_time) {
		this->delta_time = this->maximum_delta_time;
	}
	this->actual_fps = 1.0 / this->delta_time.count();

	this->elapsed_time += this->delta_time;
	this->last_frame_time = current_frame_time;
}

double LoopTimerManager::get_delta_time() const {
	return this->delta_time.count() * this->time_scale;
}

double LoopTimerManager::get_current_time() const { return this->elapsed_time.count(); }

void LoopTimerManager::advance_fixed_update() {
	this->elapsed_fixed_time += this->fixed_delta_time;
}

double LoopTimerManager::get_fixed_delta_time() const {
	return this->fixed_delta_time.count();
}

void LoopTimerManager::set_target_fps(int fps) {
	this->target_fps = fps;
	// target time per frame in seconds
	this->frame_target_time = std::chrono::duration<double>(1.0) / this->target_fps;
}

int LoopTimerManager::get_fps() const { return this->actual_fps; }

void LoopTimerManager::set_time_scale(double value) { this->time_scale = value; }

double LoopTimerManager::get_time_scale() const { return this->time_scale; }

void LoopTimerManager::enforce_frame_rate() {
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

double LoopTimerManager::get_lag() const {
	return (this->elapsed_time - this->elapsed_fixed_time).count();
}
