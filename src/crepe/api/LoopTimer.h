#pragma once

#include <cstdint>

namespace crepe::api{
class LoopTimer {
	public:
		/**
		 * \brief Get the singleton instance of LoopTimer.
		 *
		 * \return A reference to the LoopTimer instance.
		 */
		static LoopTimer& getInstance();

		/**
		 * \brief Get the current delta time for the current frame.
		 *
		 * \return Delta time in seconds since the last frame.
		 */
		double get_delta_time() const;

		/**
		 * \brief Get the current game time.
		 *
		 * \note The current game time may vary from the real-world elapsed time.
		 * It is the cumulative sum of each frame's delta time.
		 *
		 * \return Elapsed game time in milliseconds.
		 */
		int get_current_time() const;

		/**
		 * \brief Set the target frames per second (FPS).
		 *
		 * \param fps The number of frames that should be rendered per second.
		 */
		void set_fps(int fps);

		/**
		 * \brief Get the current frames per second (FPS).
		 *
		 * \return Current FPS.
		 */
		int get_fps() const;

		/**
		 * \brief Get the current game scale.
		 *
		 * \return The current game scale, where 0 = paused, 1 = normal speed, and values > 1 speed up the game.
		 */
		double get_game_scale() const;

		/**
		 * \brief Set the game scale.
		 *
		 * \param game_scale The desired game scale (0 = pause, 1 = normal speed, > 1 = speed up).
		 */
		void set_game_scale(double game_scale);

	private:
		friend class LoopManager;
		void start();
		void enforce_frame_rate();
		double get_fixed_delta_time() const;
		double get_lag() const;
		LoopTimer();
		void update();
		void advance_fixed_update();
	private:
		int fps = 50;                       ///< Current frames per second
		double game_scale = 1;              ///< Current game scale
		double maximum_delta_time = 0.25;   ///< Maximum delta time to avoid large jumps
		double delta_time = 0;              ///< Delta time for the current frame
		double frame_target_time = 1.0 / fps; ///< Target time per frame in seconds
		double fixed_delta_time = 0.02;     ///< Fixed delta time for fixed updates
		double elapsed_time = 0;             ///< Total elapsed game time
		double elapsed_fixed_time = 0;      ///< Total elapsed time for fixed updates
		uint64_t last_frame_time = 0;       ///< Time of the last frame
	};
}
