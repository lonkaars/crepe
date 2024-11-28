#include <gtest/gtest.h>
#include <gmock/gmock.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/manager/ComponentManager.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/system/ScriptSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptTest : public Test {
	Mediator m;
public:
	ComponentManager component_manager{m};
	ScriptSystem system{m};
	EventManager & event_manager = m.event_manager;

	class MyScript : public Script {
		// NOTE: explicitly stating `public:` is not required on actual scripts
	public:
		MOCK_METHOD(void, init, (), (override));
		MOCK_METHOD(void, update, (), (override));
	};

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

TEST_F(ScriptTest, Default) {
	MyScript & script = this->script;
	EXPECT_CALL(script, init()).Times(0);
	EXPECT_CALL(script, update()).Times(0);
}

TEST_F(ScriptTest, UpdateOnce) {
	MyScript & script = this->script;

	{
		InSequence seq;

		EXPECT_CALL(script, init()).Times(1);
		EXPECT_CALL(script, update()).Times(1);
		system.update();
	}

	{
		InSequence seq;

		EXPECT_CALL(script, init()).Times(0);
		EXPECT_CALL(script, update()).Times(1);
		system.update();
	}
}

TEST_F(ScriptTest, UpdateInactive) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;

	{
		InSequence seq;

		EXPECT_CALL(script, init()).Times(0);
		EXPECT_CALL(script, update()).Times(0);
		behaviorscript.active = false;
		system.update();
	}

	{
		InSequence seq;

		EXPECT_CALL(script, init()).Times(1);
		EXPECT_CALL(script, update()).Times(1);
		behaviorscript.active = true;
		system.update();
	}
}

