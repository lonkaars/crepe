#include <gtest/gtest.h>

#define protected public

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Script.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/system/ScriptSystem.h>

#include "ScriptTest.h"

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptECSTest : public ScriptTest {
public:
	class TestComponent : public Component {
		using Component::Component;
	};
};

TEST_F(ScriptECSTest, GetOwnComponent) {
	MyScript & script = this->script;
	Metadata & metadata = script.get_component<Metadata>();

	EXPECT_EQ(metadata.name, OBJ_NAME);
}

TEST_F(ScriptECSTest, GetOwnComponents) {
	const unsigned COUNT = 4;

	for (unsigned i = 0; i < COUNT; i++) entity.add_component<TestComponent>();

	MyScript & script = this->script;
	RefVector<TestComponent> components = script.get_components<TestComponent>();

	EXPECT_EQ(components.size(), COUNT);
}
