#define private public
#define protected public
#include "api/LoopManager.h"
#include "api/LoopTimer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class GameLoopTest : public ::testing::Test {
public:
LoopManager loop_manager;
LoopTimer loop_timer = LoopTimer::get_instance();
protected:
	void SetUp() override {
		loop_timer.start();
		loop_manager.start();
	}

	void TearDown() override {
		
	}
};
TEST_F(GameLoopTest, TestDeltaTime) {
    auto start_time = std::chrono::steady_clock::now();
    
    loop_timer.update();  
    double delta_time = loop_timer.get_delta_time();

    auto elapsed_time = std::chrono::steady_clock::now() - start_time;
    EXPECT_LE(delta_time, std::chrono::duration<double>(elapsed_time).count());  // delta_time should match or be slightly less
}
