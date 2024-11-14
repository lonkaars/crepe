#include "system/AudioSystem.h"
#include <gtest/gtest.h>

#include <crepe/ComponentManager.h>
#include <crepe/api/AudioSource.h>

using namespace std;
using namespace crepe;
using namespace testing;

class AudioTest : public Test {
public:
	ComponentManager component_manager{};
	AudioSystem system {component_manager};

	void SetUp() override {
		auto & mgr = this->component_manager;
		GameObject entity = mgr.new_object("name");
	}
};

TEST_F(AudioTest, Default) {
}

