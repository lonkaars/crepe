#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>
#define private public
#define protected public
#include <crepe/api/LoopManager.h>
#include <crepe/manager/EventManager.h>
#include <crepe/manager/LoopTimerManager.h>
using namespace std::chrono;
using namespace crepe;

class DISABLED_LoopManagerTest : public ::testing::Test {
protected:
	class TestGameLoop : public crepe::LoopManager {
	public:
		MOCK_METHOD(void, fixed_update, (), (override));
		MOCK_METHOD(void, frame_update, (), (override));
	};

	TestGameLoop test_loop;
	void SetUp() override {}
};

TEST_F(DISABLED_LoopManagerTest, FixedUpdate) {
	// Arrange
	test_loop.loop_timer.set_target_framerate(60);

	// Set expectations for the mock calls
	EXPECT_CALL(test_loop, frame_update).Times(::testing::Between(55, 65));
	EXPECT_CALL(test_loop, fixed_update).Times(::testing::Between(48, 52));

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

TEST_F(DISABLED_LoopManagerTest, ScaledFixedUpdate) {
	// Arrange
	test_loop.loop_timer.set_target_framerate(60);

	// Set expectations for the mock calls
	EXPECT_CALL(test_loop, frame_update).Times(::testing::Between(55, 65));
	EXPECT_CALL(test_loop, fixed_update).Times(::testing::Between(48, 52));

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

TEST_F(DISABLED_LoopManagerTest, ShutDown) {
	// Arrange
	test_loop.loop_timer.set_target_framerate(60);
	// Start the loop in a separate thread
	std::thread loop_thread([&]() { test_loop.start(); });
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	test_loop.event_manager.trigger_event<ShutDownEvent>(ShutDownEvent{});
	// Wait for the loop thread to finish
	loop_thread.join();
}

