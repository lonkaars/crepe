#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Vector2.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/system/ScriptSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class MyEvent : public Event { };

class ScriptTest : public Test {
public:
	ComponentManager component_manager{};
	ScriptSystem system{component_manager};
	EventManager & evmgr = EventManager::get_instance();

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
		void update() {
			this->update_count++;
		}

	public:
		unsigned init_count = 0;
		unsigned update_count = 0;
		unsigned event_count = 0;
	};

	BehaviorScript * behaviorscript_ref = nullptr;
	MyScript * script_ref = nullptr;

	void SetUp() override {
		auto & mgr = this->component_manager;
		GameObject entity = mgr.new_object("name");
		BehaviorScript & component = entity.add_component<BehaviorScript>();

		this->behaviorscript_ref = &component;
		EXPECT_EQ(this->behaviorscript_ref->script.get(), nullptr);
		component.set_script<MyScript>();
		ASSERT_NE(this->behaviorscript_ref->script.get(), nullptr);

		this->script_ref = (MyScript *) this->behaviorscript_ref->script.get();
		ASSERT_NE(this->script_ref, nullptr);

		// sanity
		ASSERT_EQ(script_ref->init_count, 0);
		ASSERT_EQ(script_ref->update_count, 0);
		ASSERT_EQ(script_ref->event_count, 0);
	}
};

TEST_F(ScriptTest, Default) {
	EXPECT_EQ(0, this->script_ref->init_count);
	EXPECT_EQ(0, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);
}

TEST_F(ScriptTest, UpdateOnce) {
	this->system.update();
	EXPECT_EQ(1, this->script_ref->init_count);
	EXPECT_EQ(1, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);
}

TEST_F(ScriptTest, UpdateInactive) {
	this->behaviorscript_ref->active = false;
	this->system.update();
	EXPECT_EQ(0, this->script_ref->init_count);
	EXPECT_EQ(0, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);

	this->behaviorscript_ref->active = true;
	this->system.update();
	EXPECT_EQ(1, this->script_ref->init_count);
	EXPECT_EQ(1, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);
}

TEST_F(ScriptTest, EventInactive) {
	this->system.update();
	this->behaviorscript_ref->active = false;
	EXPECT_EQ(1, this->script_ref->init_count);
	EXPECT_EQ(1, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);

	this->evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, this->script_ref->init_count);
	EXPECT_EQ(1, this->script_ref->update_count);
	EXPECT_EQ(0, this->script_ref->event_count);

	this->behaviorscript_ref->active = true;
	this->evmgr.trigger_event<MyEvent>();
	EXPECT_EQ(1, this->script_ref->init_count);
	EXPECT_EQ(1, this->script_ref->update_count);
	EXPECT_EQ(1, this->script_ref->event_count);
}

TEST_F(ScriptTest, ListScripts) {
	size_t script_count = 0;
	for (auto & _ : this->system.get_scripts()) {
		script_count++;
	}
	ASSERT_EQ(1, script_count);
}

