#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#define private public
#define protected public
#include <crepe/manager/LoopTimerManager.h>
#include <crepe/manager/Mediator.h>
using namespace std::chrono;
using namespace crepe;

class LoopTimerTest : public ::testing::Test {
protected:
	Mediator mediator;
	LoopTimerManager loop_timer{mediator};

	void SetUp() override { loop_timer.start(); }
};

TEST_F(LoopTimerTest, EnforcesTargetFrameRate) {
	// Set the target FPS to 60 (which gives a target time per frame of ~16.67 ms)
	loop_timer.set_target_framerate(60);

	auto start_time = steady_clock::now();
	loop_timer.enforce_frame_rate();

	auto elapsed_time = steady_clock::now() - start_time;
	auto elapsed_ms = duration_cast<milliseconds>(elapsed_time).count();

	// For 60 FPS, the target frame time is around 16.67ms
	ASSERT_NEAR(elapsed_ms, 16.7, 1);
}

TEST_F(LoopTimerTest, SetTargetFps) {
	// Set the target FPS to 120
	loop_timer.set_target_framerate(120);

	// Calculate the expected frame time (~8.33ms per frame)
	duration_t expected_frame_time = std::chrono::duration<float>(1.0 / 120.0);

	ASSERT_NEAR(loop_timer.frame_target_time.count(), expected_frame_time.count(), 0.001);
}

TEST_F(LoopTimerTest, DeltaTimeCalculation) {
	// Set the target FPS to 60 (16.67 ms per frame)
	loop_timer.set_target_framerate(60);

	auto start_time = steady_clock::now();
	loop_timer.update();
	auto end_time = steady_clock::now();

	// Check the delta time
	duration_t delta_time = loop_timer.get_delta_time();

	auto elapsed_time = duration_cast<seconds>(end_time - start_time).count();

	// Assert that delta_time is close to the elapsed time
	ASSERT_NEAR(delta_time.count(), elapsed_time, 1);
}

TEST_F(LoopTimerTest, getCurrentTime) {
	// Set the target FPS to 60 (16.67 ms per frame)
	loop_timer.set_target_framerate(60);

	auto start_time = steady_clock::now();

	// Sleep
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	loop_timer.update();

	auto end_time = steady_clock::now();

	// Get the elapsed time in seconds as a double
	auto elapsed_time
		= std::chrono::duration_cast<elapsed_time_t>(end_time - start_time).count();

	ASSERT_NEAR(loop_timer.get_elapsed_time().count(), elapsed_time, 5);
}
TEST_F(LoopTimerTest, getFPS) {
	// Set the target FPS to 60 (which gives a target time per frame of ~16.67 ms)
	loop_timer.set_target_framerate(60);

	auto start_time = steady_clock::now();
	loop_timer.enforce_frame_rate();

	auto elapsed_time = steady_clock::now() - start_time;
	loop_timer.update();
	unsigned int fps = loop_timer.get_fps();
	auto elapsed_ms = duration_cast<milliseconds>(elapsed_time).count();

	// For 60 FPS, the target frame time is around 16.67ms
	ASSERT_NEAR(elapsed_ms, 16.7, 1);
	ASSERT_NEAR(fps, 60, 2);
}
