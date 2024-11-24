#define private public
#define protected public
#include "api/LoopManager.h"
#include "api/LoopTimer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class LoopTimerTest : public ::testing::Test {
public:
LoopTimer loop_timer = LoopTimer::get_instance();
protected:
	void SetUp() override {
		loop_timer.start();
	}

	void TearDown() override {
		
	}
};
TEST_F(LoopTimerTest, TestDeltaTime) {
    auto start_time = std::chrono::steady_clock::now();
    
    loop_timer.update();  
    double delta_time = loop_timer.get_delta_time();

    auto elapsed_time = std::chrono::steady_clock::now() - start_time;
    EXPECT_LE(delta_time, std::chrono::duration<double>(elapsed_time).count());
}
