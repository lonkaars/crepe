#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Vector2.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/EventManager.h>
#include <crepe/system/ScriptSystem.h>

#include "ScriptTest.h"

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptEventTest : public ScriptTest {
public:
	EventManager & event_manager = mediator.event_manager;

	struct MyEvent : public Event {};
};

TEST_F(ScriptEventTest, Default) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;
	EventManager & evmgr = this->event_manager;

	unsigned event_count = 0;
	script.subscribe<MyEvent>([&](const MyEvent &) {
		event_count++;
		return true;
	});

	system.fixed_update();
	behaviorscript.active = false;
	EXPECT_EQ(0, event_count);

	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(0, event_count);

	behaviorscript.active = true;
	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, event_count);
}
