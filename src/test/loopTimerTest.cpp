#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#define private public
#define protected public
#include "api/LoopTimer.h"

using namespace std::chrono;
using namespace crepe;

class LoopTimerTest : public ::testing::Test {
protected:
    LoopTimer loop_timer;

    void SetUp() override {
        loop_timer.start(); 
    }
};
TEST_F(LoopTimerTest, EnforcesTargetFrameRate) {
    // Set the target FPS to 60 (which gives a target time per frame of ~16.67 ms)
    loop_timer.set_target_fps(60);

    auto start_time = steady_clock::now();
    loop_timer.enforce_frame_rate();

    auto elapsed_time = steady_clock::now() - start_time;
    auto elapsed_ms = duration_cast<milliseconds>(elapsed_time).count();

    // For 60 FPS, the target frame time is around 16.67ms
    ASSERT_GE(elapsed_ms, 16);  // Make sure it's at least 16 ms (could be slightly more)
    ASSERT_LE(elapsed_ms, 18);  // Ensure it's not too much longer
}
TEST_F(LoopTimerTest, SetTargetFps) {
    // Set the target FPS to 120
    loop_timer.set_target_fps(120);
    
    // Calculate the expected frame time (~8.33ms per frame)
    auto expected_frame_time = std::chrono::duration<double>(1.0 / 120.0);

    ASSERT_NEAR(loop_timer.frame_target_time.count(), expected_frame_time.count(), 0.001);
}
TEST_F(LoopTimerTest, DeltaTimeCalculation) {
    // Set the target FPS to 60 (16.67 ms per frame)
    loop_timer.set_target_fps(60);

    auto start_time = steady_clock::now();
    loop_timer.update();
    auto end_time = steady_clock::now();

    // Check the delta time
    double delta_time = loop_timer.get_delta_time();

    auto elapsed_time = duration_cast<milliseconds>(end_time - start_time).count();
    
    // Assert that delta_time is close to the elapsed time
    ASSERT_GE(delta_time, elapsed_time / 1000.0);
    ASSERT_LE(delta_time, (elapsed_time + 2) / 1000.0);
}

