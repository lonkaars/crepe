#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#define private public
#define protected public
#include "api/LoopTimer.h"
#include "api/LoopManager.h"

using namespace std::chrono;
using namespace crepe;

class LoopManagerTest : public ::testing::Test {
protected:
    LoopManager loop_manager;

    void SetUp() override {
        // Setting up loop manager and start the loop
        loop_manager.loop_timer->set_target_fps(60);
    }
};

//Test to check if exactly 5 fixed updates are done every second (50Hz)
TEST_F(LoopManagerTest, FixedUpdate) {
	loop_manager.loop_timer->fixed_delta_time = std::chrono::milliseconds(20); 
	loop_manager.loop_timer->set_target_fps(50);
    int fixed_update_count = 0;
	loop_manager.loop_timer->start();
    // We want to simulate the game loop for about 1 second
    auto start_time = steady_clock::now();

    // Simulate the game loop for 1 second
    while (duration_cast<milliseconds>(steady_clock::now() - start_time) < std::chrono::milliseconds(1000)) {
		loop_manager.loop_timer->update();
        // Simulate processing fixed updates while there's lag to advance
        while (loop_manager.loop_timer->get_lag() >= loop_manager.loop_timer->get_fixed_delta_time()) {
            fixed_update_count++;
            loop_manager.loop_timer->advance_fixed_update();
        }
        
        loop_manager.loop_timer->enforce_frame_rate();
    }
	// gameloop is 99 because it first takes 20 millisecond to build the lag to execute the fixed loop
    ASSERT_EQ(fixed_update_count, 50);
}
