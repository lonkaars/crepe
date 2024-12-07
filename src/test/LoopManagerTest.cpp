#include <chrono>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#define private public
#define protected public
#include <crepe/api/LoopManager.h>
#include <crepe/manager/LoopTimerManager.h>
#include <crepe/manager/EventManager.h>
using namespace std::chrono;
using namespace crepe;

class LoopManagerTest : public ::testing::Test {
protected:
    class TestGameLoop : public crepe::LoopManager {
    public:
    	MOCK_METHOD(void, fixed_update, (), (override));
        MOCK_METHOD(void, update, (), (override));
		MOCK_METHOD(void, render, (), (override));
    };

    TestGameLoop test_loop;
	// LoopManager test_loop;
    void SetUp() override {
		
    }
};

TEST_F(LoopManagerTest, FixedUpdate) {
    // Arrange
    test_loop.loop_timer.set_target_fps(60);

    // Set expectations for the mock calls
    EXPECT_CALL(test_loop, render).Times(::testing::Exactly(60)); 
	EXPECT_CALL(test_loop, update).Times(::testing::Exactly(60));
    EXPECT_CALL(test_loop, fixed_update).Times(::testing::Exactly(50));

    // Start the loop in a separate thread
    std::thread loop_thread([&]() { test_loop.start(); });

    // Let the loop run for exactly 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the game loop
    test_loop.game_running = false;
    // Wait for the loop thread to finish
    loop_thread.join();

    // Test finished
}
TEST_F(LoopManagerTest, ShutDown) {
    // Arrange
    test_loop.loop_timer.set_target_fps(60);

	EXPECT_CALL(test_loop, render).Times(::testing::AtLeast(1)); 
	EXPECT_CALL(test_loop, update).Times(::testing::AtLeast(1));
    EXPECT_CALL(test_loop, fixed_update).Times(::testing::AtLeast(1));
    // Start the loop in a separate thread
    std::thread loop_thread([&]() { test_loop.start(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
	test_loop.event_manager.trigger_event<ShutDownEvent>(ShutDownEvent{});
    // Wait for the loop thread to finish
    loop_thread.join();

    // Test finished
}

