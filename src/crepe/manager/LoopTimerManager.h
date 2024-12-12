#pragma once

#include <chrono>

#include "Manager.h"

namespace crepe {

typedef std::chrono::duration<double> duration_t;
typedef std::chrono::duration<unsigned long long, std::micro> elapsed_time_t;

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
	LoopTimerManager(Mediator & mediator);
	/**
	 * \brief Get the current delta time for the current frame.
	 *	
	 * This value represents the estimated frame duration of the current frame.
	 * This value can be used in the frame_update to convert pixel based values to time based values.
	 * 
	 * \return Delta time in seconds since the last frame.
	 */
	duration_t get_delta_time() const;

	/**
	 * \brief Get the current elapsed time (total time passed )
	 *
	 * \note The current game time may vary from real-world elapsed time. It is the cumulative
	 * sum of each frame's delta time.
	 *
	 * \return Elapsed game time in seconds.
	 */
	elapsed_time_t get_elapsed_time() const;

	/**
	 * \brief Set the target frames per second (FPS).
	 *
	 * \param fps The desired frames rendered per second.
	 */
	void set_target_framerate(unsigned fps);

	/**
	 * \brief Get the current frames per second (FPS).
	 *
	 * \return Current FPS.
	 */
	unsigned get_fps() const;

	/**
	 * \brief Get the current time scale.
	 *
	 * \return The current time scale, where (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up).
	 * up the game.
	 */
	float get_time_scale() const;

	/**
	 * \brief Set the time scale.
	 *
	 * time_scale is a value that changes the delta time that can be retrieved using get_delta_time function. 
	 * 
	 * \param time_scale The desired time scale (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up).
	 */
	void set_time_scale(double time_scale);

	/**
	 * \brief Get the fixed delta time in seconds without scaling by the time scale.
	 *
	 * This value is used in the LoopManager to determine how many times 
	 * the fixed_update should be called within a given interval.
	 *
	 * \return The unscaled fixed delta time in seconds.
	 */
	duration_t get_fixed_delta_time() const;

	/**
	 * \brief Set the fixed_delta_time in seconds.
	 * 
	 * \param seconds fixed_delta_time in seconds.
	 * 
	 * The fixed_delta_time value is used to determine how many times per second the fixed_update and process_input functions are called.
	 * 
	 */
	void set_fixed_delta_time(float seconds);

	/**
	 * \brief Retrieves the scaled fixed delta time in seconds.
	 *
	 * The scaled fixed delta time is the timing value used within the `fixed_update` function. 
	 * It is adjusted by the time_scale to account for any changes in the simulation's 
	 * speed.
	 *
	 * \return The fixed delta time, scaled by the current time scale, in seconds.
	 */
	float get_scaled_fixed_delta_time() const;

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
	duration_t get_lag() const;

	/**
	 * \brief Update the timer to the current frame.
	 *
	 * Calculates and updates the delta time for the current frame and adds it to the cumulative
	 * game time.
	 */
	void update();

	/**
	 * \brief Progress the elapsed fixed time by the fixed delta time interval.
	 *
	 * This method advances the game's fixed update loop by adding the fixed_delta_time 
	 * to elapsed_fixed_time, ensuring the fixed update catches up with the elapsed time.
	 */
	void advance_fixed_elapsed_time();

private:
	//! Target frames per second.
	unsigned target_fps = 60;
	//! Actual frames per second.
	unsigned actual_fps = 0;
	//! Time scale for speeding up or slowing down the game (0 = pause, < 1 = slow down, 1 = normal speed, > 1 = speed up).
	float time_scale = 1;
	//! Maximum delta time in seconds to avoid large jumps.
	duration_t maximum_delta_time{0.25};
	//! Delta time for the current frame in seconds.
	duration_t delta_time{0.0};
	//! Target time per frame in seconds
	duration_t frame_target_time{1.0 / target_fps};
	//! Fixed delta time for fixed updates in seconds.
	duration_t fixed_delta_time{1.0 / 50.0};
	//! Total elapsed game time in microseconds.
	elapsed_time_t elapsed_time{0};
	//! Total elapsed time for fixed updates in microseconds.
	elapsed_time_t elapsed_fixed_time{0};

	typedef std::chrono::steady_clock::time_point time_point_t;
	//! Time of the last frame.
	time_point_t last_frame_time;
};

} // namespace crepe
