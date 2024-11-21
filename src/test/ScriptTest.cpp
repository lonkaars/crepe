#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Vector2.h>
#include <crepe/system/ScriptSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class MyEvent : public Event {};

class ScriptTest : public Test {
public:
	ComponentManager component_manager{};
	ScriptSystem system{component_manager};
	EventManager & event_manager = EventManager::get_instance();

	class MyScript : public Script {
		// NOTE: default (private) visibility of init and update shouldn't cause
		// issues!
		void init() {
			this->init_count++;

			subscribe<MyEvent>([this](const MyEvent &) {
				this->event_count++;
				return true;
			});

			// init should never be called more than once
			EXPECT_LE(this->init_count, 1);
		}
		void update() { this->update_count++; }

	public:
		unsigned init_count = 0;
		unsigned update_count = 0;
		unsigned event_count = 0;
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

		// sanity
		MyScript & script = this->script;
		ASSERT_EQ(script.init_count, 0);
		ASSERT_EQ(script.update_count, 0);
		ASSERT_EQ(script.event_count, 0);
	}
};

TEST_F(ScriptTest, Default) {
	MyScript & script = this->script;
	EXPECT_EQ(0, script.init_count);
	EXPECT_EQ(0, script.update_count);
	EXPECT_EQ(0, script.event_count);
}

TEST_F(ScriptTest, UpdateOnce) {
	MyScript & script = this->script;

	system.update();
	EXPECT_EQ(1, script.init_count);
	EXPECT_EQ(1, script.update_count);
	EXPECT_EQ(0, script.event_count);
}

TEST_F(ScriptTest, UpdateInactive) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;

	behaviorscript.active = false;
	system.update();
	EXPECT_EQ(0, script.init_count);
	EXPECT_EQ(0, script.update_count);
	EXPECT_EQ(0, script.event_count);

	behaviorscript.active = true;
	system.update();
	EXPECT_EQ(1, script.init_count);
	EXPECT_EQ(1, script.update_count);
	EXPECT_EQ(0, script.event_count);
}

TEST_F(ScriptTest, EventInactive) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;
	EventManager & evmgr = this->event_manager;

	system.update();
	behaviorscript.active = false;
	EXPECT_EQ(1, script.init_count);
	EXPECT_EQ(1, script.update_count);
	EXPECT_EQ(0, script.event_count);

	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, script.init_count);
	EXPECT_EQ(1, script.update_count);
	EXPECT_EQ(0, script.event_count);

	behaviorscript.active = true;
	evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, script.init_count);
	EXPECT_EQ(1, script.update_count);
	EXPECT_EQ(1, script.event_count);
}
