#pragma once

#include <chrono>

#include "Manager.h"

namespace crepe {

/**
 * \brief Manages timing and frame rate for the game loop.
 * 
 * The LoopTimerManager class is responsible for calculating and managing timing functions 
 * such as delta time, frames per second (FPS), fixed time steps, and time scaling. It ensures 
 * consistent frame updates and supports game loop operations, such as handling fixed updates 
 * for physics and other time-sensitive operations.
 */
class LoopTimerManager : public Manager {
public:
	/**
	 * \param mediator A reference to a Mediator object used for transfering managers.
	 */
	LoopTimerManager(Mediator &mediator);
	/**
	 * \brief Get the current delta time for the current frame.
	 *
	 * \return Delta time in seconds since the last frame.
	 */
	double get_delta_time() const;

	/**
	 * \brief Get the current game time.
	 *
	 * \note The current game time may vary from real-world elapsed time. It is the cumulative
	 * sum of each frame's delta time.
	 *
	 * \return Elapsed game time in seconds.
	 */
	double get_current_time() const;

	/**
	 * \brief Set the target frames per second (FPS).
	 *
	 * \param fps The desired frames rendered per second.
	 */
	void set_target_fps(int fps);

	/**
	 * \brief Get the current frames per second (FPS).
	 *
	 * \return Current FPS.
	 */
	int get_fps() const;

	/**
	 * \brief Get the current time scale.
	 *
	 * \return The current time scale, where (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up).
	 * up the game.
	 */
	double get_time_scale() const;

	/**
	 * \brief Set the time scale.
	 *
	 * time_scale is a value that changes the delta time that can be retrieved using get_delta_time function. 
	 * 
	 * \param time_scale The desired time scale (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up).
	 */
	void set_time_scale(double time_scale);

	/**
	 * \brief Get the scaled fixed delta time in seconds.
	 *
	 * The fixed delta time is used for operations that require uniform time steps, 
	 * such as physics calculations, and is scaled by the current time scale.
	 *
	 * \return The fixed delta time, scaled by time scale, in seconds.
	 */
	double get_fixed_loop_interval() const;

	/**
	 * \brief Get the fixed delta time in seconds without scaling by the time scale.
	 *
	 * This value is used in the LoopManager to determine how many times 
	 * the fixed_update should be called within a given interval.
	 *
	 * \return The unscaled fixed delta time in seconds.
	 */
	double get_fixed_delta_time() const;

	/**
	 * \brief Set the fixed_delta_time in seconds.
	 * 
	 * \param seconds fixed_delta_time in seconds.
	 * 
	 * The fixed_delta_time value is used to determine how many times per second the fixed_update and process_input functions are called.
	 */
	void set_fixed_delta_time(double seconds);

private:
	//! Friend relation to use start,enforce_frame_rate,get_lag,update,advance_fixed_update.
	friend class LoopManager;

	/**
	 * \brief Start the loop timer.
	 *
	 * Initializes the timer to begin tracking frame times.
	 */
	void start();
	/**
	 * \brief Enforce the frame rate limit.
	 *
	 * Ensures that the game loop does not exceed the target FPS by delaying frame updates as
	 * necessary.
	 */
	void enforce_frame_rate();
	/**
	 * \brief Get the accumulated lag in the game loop.
	 *
	 * Lag represents the difference between the target frame time and the actual frame time,
	 * useful for managing fixed update intervals.
	 *
	 * \return Accumulated lag in seconds.
	 */
	double get_lag() const;

	/**
	 * \brief Update the timer to the current frame.
	 *
	 * Calculates and updates the delta time for the current frame and adds it to the cumulative
	 * game time.
	 */
	void update();

	/**
	 * \brief Advance the game loop by a fixed update interval.
	 *
	 * This method progresses the game state by a consistent, fixed time step, allowing for
	 * stable updates independent of frame rate fluctuations.
	 */
	void advance_fixed_update();

private:
	//! Target frames per second
	int target_fps = 60;
	//! Actual frames per second
	int actual_fps = 0;
	//! Time scale for speeding up or slowing down the game (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up)
	double time_scale = 1;
	//! Maximum delta time in seconds to avoid large jumps
	std::chrono::duration<double> maximum_delta_time{0.25};
	//! Delta time for the current frame in seconds
	std::chrono::duration<double> delta_time{0.0};
	//! Target time per frame in seconds
	std::chrono::duration<double> frame_target_time
		= std::chrono::duration<double>(1.0) / target_fps;
	//! Fixed delta time for fixed updates in seconds
	std::chrono::duration<double> fixed_delta_time = std::chrono::duration<double>(1.0) / 50.0;
	//! Total elapsed game time in seconds
	std::chrono::duration<double> elapsed_time{0.0};
	//! Total elapsed time for fixed updates in seconds
	std::chrono::duration<double> elapsed_fixed_time{0.0};
	//! Time of the last frame
	std::chrono::steady_clock::time_point last_frame_time;
};

} // namespace crepe
