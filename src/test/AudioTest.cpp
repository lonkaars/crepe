#include "system/AudioSystem.h"
#include <gtest/gtest.h>

#include <crepe/ComponentManager.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/GameObject.h>

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
		entity.add_component<AudioSource>("../mwe/audio/sfx1.wav");
	}
};

TEST_F(AudioTest, Default) {
}

