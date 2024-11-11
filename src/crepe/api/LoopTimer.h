 #pragma once

#include <cstdint>
#include <chrono>

namespace crepe {

class LoopTimer {
public:
    /**
     * \brief Get the singleton instance of LoopTimer.
     *
     * \return A reference to the LoopTimer instance.
     */
    static LoopTimer& get_instance();

    /**
     * \brief Get the current delta time for the current frame.
     *
     * \return Delta time in seconds since the last frame.
     */
    double get_delta_time() const;

    /**
     * \brief Get the current game time.
     *
     * \note The current game time may vary from real-world elapsed time.
     * It is the cumulative sum of each frame's delta time.
     *
     * \return Elapsed game time in seconds.
     */
    double get_current_time() const;

    /**
     * \brief Set the target frames per second (FPS).
     *
     * \param fps The desired frames rendered per second.
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

    /**
     * \brief Start the loop timer.
     *
     * Initializes the timer to begin tracking frame times.
     */
    void start();

    /**
     * \brief Enforce the frame rate limit.
     *
     * Ensures that the game loop does not exceed the target FPS by delaying
     * frame updates as necessary.
     */
    void enforce_frame_rate();

    /**
     * \brief Get the fixed delta time for consistent updates.
     *
     * Fixed delta time is used for operations that require uniform time steps,
     * such as physics calculations.
     *
     * \return Fixed delta time in seconds.
     */
    double get_fixed_delta_time() const;

    /**
     * \brief Get the accumulated lag in the game loop.
     *
     * Lag represents the difference between the target frame time and the
     * actual frame time, useful for managing fixed update intervals.
     *
     * \return Accumulated lag in seconds.
     */
    double get_lag() const;

    /**
     * \brief Construct a new LoopTimer object.
     *
     * Private constructor for singleton pattern to restrict instantiation
     * outside the class.
     */
    LoopTimer();

    /**
     * \brief Update the timer to the current frame.
     *
     * Calculates and updates the delta time for the current frame and adds it to
     * the cumulative game time.
     */
    void update();

    /**
     * \brief Advance the game loop by a fixed update interval.
     *
     * This method progresses the game state by a consistent, fixed time step,
     * allowing for stable updates independent of frame rate fluctuations.
     */
    void advance_fixed_update();

private:
    //! Current frames per second
    int fps = 50;
    //! Current game scale
    double game_scale = 1;
    //! Maximum delta time in seconds to avoid large jumps
    std::chrono::duration<double>  maximum_delta_time{0.25};
    //! Delta time for the current frame in seconds
    std::chrono::duration<double> delta_time{0.0};
    //! Target time per frame in seconds
    std::chrono::duration<double> frame_target_time = std::chrono::seconds(1) / fps;
    //! Fixed delta time for fixed updates in seconds
    std::chrono::duration<double> fixed_delta_time = std::chrono::seconds(1) / 50;
    //! Total elapsed game time in seconds
    std::chrono::duration<double> elapsed_time{0.0};
    //! Total elapsed time for fixed updates in seconds
    std::chrono::duration<double> elapsed_fixed_time{0.0};
    //! Time of the last frame 
    std::chrono::steady_clock::time_point last_frame_time;
};

} // namespace crepe
