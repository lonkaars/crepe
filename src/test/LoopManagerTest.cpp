#include <chrono>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#define private public
#define protected public
#include "api/LoopManager.h"
#include "api/LoopTimer.h"

using namespace std::chrono;
using namespace crepe;

class LoopManagerTest : public ::testing::Test {
protected:
    class TestGameLoop : public crepe::LoopManager {
    public:
        MOCK_METHOD(void, fixed_update, (), (override));
        MOCK_METHOD(void, update, (), (override));
    };

    TestGameLoop test_loop;

    void SetUp() override {
        test_loop.loop_timer->set_target_fps(60); // Example target FPS
    }
};

// Test to check if exactly 50 fixed updates occur in 1 second (50Hz)
TEST_F(LoopManagerTest, FixedUpdate) {
    // Arrange
    using ::testing::AtLeast;
    using ::testing::Exactly;

    test_loop.loop_timer->fixed_delta_time = std::chrono::milliseconds(20);
	test_loop.start();
    // Expect the `fixed_update` method to be called exactly 50 times
    EXPECT_CALL(test_loop, fixed_update()).Times(Exactly(50));

    auto start_time = steady_clock::now();

    // Act: Simulate the game loop for 1 second
    while (duration_cast<milliseconds>(steady_clock::now() - start_time) < std::chrono::milliseconds(1000)) {

    }
	test_loop.game_running = false;
}
