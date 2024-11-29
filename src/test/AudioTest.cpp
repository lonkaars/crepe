#include <gtest/gtest.h>

#include <crepe/manager/ComponentManager.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/GameObject.h>
#include <crepe/system/AudioSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class AudioTest : public Test {
	Mediator mediator;
public:
	ComponentManager component_manager{mediator};
	AudioSystem system {mediator};

	void SetUp() override {
		auto & mgr = this->component_manager;
		GameObject entity = mgr.new_object("name");
		entity.add_component<AudioSource>("mwe/audio/sfx1.wav");
	}
};

TEST_F(AudioTest, Default) {
}

