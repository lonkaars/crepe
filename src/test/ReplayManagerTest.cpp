#include <gtest/gtest.h>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/manager/ReplayManager.h>
#include <crepe/system/ReplaySystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ReplayManagerTest : public Test {
	Mediator mediator;

public:
	ComponentManager component_manager{mediator};
	ReplayManager replay_manager{mediator};
	ReplaySystem replay_system{mediator};

	GameObject entity = component_manager.new_object("foo");
	Transform & entity_transform
		= component_manager.get_components_by_id<Transform>(entity.id).back();
	Metadata & entity_metadata
		= component_manager.get_components_by_id<Metadata>(entity.id).back();
};

TEST_F(ReplayManagerTest, Default) {
	// replay_manager.record_start();

	// replay_system.fixed_update();
	// entity_transform.position += {1, 1};
	// replay_system.fixed_update();
	// entity_transform.position += {1, 1};
	// replay_system.fixed_update();

	// recording_t recording = replay_manager.record_end();
}
