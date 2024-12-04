#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#define private public
#define protected public
#include "api/LoopTimer.h"
#include "api/LoopManager.h"

using namespace std::chrono;
using namespace crepe;

class LoopTimerTest : public ::testing::Test {
protected:
    LoopManager loop_manager;

    void SetUp() override {
        // Setting up loop manager and start the loop
        loop_manager.setup();
        loop_manager.loop_timer->set_target_fps(60);
    }
};

// Test to check if exactly 5 fixed updates are done every second (50Hz)
TEST_F(LoopTimerTest, FixedUpdateCalledAt50Hz) {
    // Set target fixed delta time to 20ms (50Hz fixed updates)
    loop_manager.loop_timer->set_fixed_delta_time(milliseconds(20));

    int fixed_update_count = 0;

    // We want to simulate the game loop for about 1 second
    auto start_time = steady_clock::now();

    // Simulate the game loop for 1 second
    while (duration_cast<seconds>(steady_clock::now() - start_time).count() < 1) {
        loop_manager.loop_timer->update();

        // Simulate processing fixed updates while there's lag to advance
        while (loop_manager.loop_timer->get_lag() >= loop_manager.loop_timer->get_fixed_delta_time()) {
            loop_manager.fixed_update();  // Process fixed update
            fixed_update_count++;         // Count the number of fixed updates
            loop_manager.loop_timer->advance_fixed_update();
        }
        
        // We do not need to call render or update for this test
        loop_manager.loop_timer->enforce_frame_rate();  // Enforce the frame rate (this would normally go to the display)
    }

    // We expect 5 fixed updates to occur in 1 second at 50Hz
    ASSERT_EQ(fixed_update_count, 5);
}
