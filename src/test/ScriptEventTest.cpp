#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/EventManager.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Vector2.h>
#include <crepe/system/ScriptSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptEventTest : public Test {
	Mediator m;
public:
	ComponentManager component_manager{m};
	ScriptSystem system{m};
	EventManager & event_manager = m.event_manager;

	class MyEvent : public Event {};
	class MyScript : public Script {};

	OptionalRef<BehaviorScript> behaviorscript;
	OptionalRef<MyScript> script;

	void SetUp() override {
		auto & mgr = this->component_manager;
		GameObject entity = mgr.new_object("name");
		BehaviorScript & component = entity.add_component<BehaviorScript>();

		this->behaviorscript = component;
		ASSERT_TRUE(this->behaviorscript);
		EXPECT_EQ(component.script.get(), nullptr);
		component.set_script<MyScript>();
		ASSERT_NE(component.script.get(), nullptr);

		this->script = *(MyScript *) component.script.get();
		ASSERT_TRUE(this->script);
	}
};

TEST_F(ScriptEventTest, Inactive) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;
	EventManager & evmgr = this->event_manager;

	unsigned event_count = 0;
	script.subscribe<MyEvent>([&](const MyEvent &){
		event_count++;
		return true;
	});

	system.update();
	behaviorscript.active = false;
	EXPECT_EQ(0, event_count);

	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(0, event_count);

	behaviorscript.active = true;
	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, event_count);
}

