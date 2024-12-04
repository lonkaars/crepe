#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "api/LoopTimer.h"

using namespace std::chrono;
using namespace crepe;

class LoopTimerTest : public ::testing::Test {
protected:
    LoopTimer loop_timer;

    void SetUp() override {
        loop_timer.start(); // Reset loop timer before each test.
    }
};
TEST_F(LoopTimerTest, EnforcesTargetFrameRate) {
    // Set the target FPS to 60 (which gives a target time per frame of ~16.67 ms)
    loop_timer.set_target_fps(60);

    // Simulate a short update (frame duration less than the target frame time)
    auto start_time = steady_clock::now();
    loop_timer.enforce_frame_rate(); // Enforce the frame rate

    // Check that the loop timer's current time is greater than or equal to the target frame time
    auto elapsed_time = steady_clock::now() - start_time;
    auto elapsed_ms = duration_cast<milliseconds>(elapsed_time).count();

    // Assert that the elapsed time is close to the target frame time
    // For 60 FPS, the target frame time is around 16.67ms
    ASSERT_GE(elapsed_ms, 16);  // Make sure it's at least 16 ms (could be slightly more)
    ASSERT_LE(elapsed_ms, 18);  // Ensure it's not too much longer
}
