#include <gmock/gmock.h>
#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include "ScriptTest.h"

using namespace std;
using namespace crepe;
using namespace testing;

void ScriptTest::SetUp() {
	auto & mgr = this->component_manager;
	BehaviorScript & component = entity.add_component<BehaviorScript>();

	this->behaviorscript = component;
	ASSERT_TRUE(this->behaviorscript);
	EXPECT_EQ(component.script.get(), nullptr);
	component.set_script<NiceMock<MyScript>>();
	ASSERT_NE(component.script.get(), nullptr);

	this->script = *(MyScript *) component.script.get();
	ASSERT_TRUE(this->script);
}

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

TEST_F(ScriptTest, SaveManager) {
	MyScript & script = this->script;

	EXPECT_EQ(&script.get_save_manager(), &this->save_manager);
}

TEST_F(ScriptTest, LoopTimerManager) {
	MyScript & script = this->script;

	EXPECT_EQ(&script.get_loop_timer(), &this->loop_timer);
}

