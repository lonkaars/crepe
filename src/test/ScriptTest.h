#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Script.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/system/ScriptSystem.h>

class ScriptTest : public testing::Test {
protected:
	crepe::Mediator mediator;
	static constexpr const char * OBJ_NAME = "foo";

public:
	crepe::ComponentManager component_manager{mediator};
	crepe::ScriptSystem system{mediator};
	crepe::GameObject entity = component_manager.new_object(OBJ_NAME);

	class MyScript : public crepe::Script {
		// NOTE: explicitly stating `public:` is not required on actual scripts

	public:
		MOCK_METHOD(void, init, (), (override));
		MOCK_METHOD(void, update, (), (override));
	};

	crepe::OptionalRef<crepe::BehaviorScript> behaviorscript;
	crepe::OptionalRef<MyScript> script;

	virtual void SetUp();
};
