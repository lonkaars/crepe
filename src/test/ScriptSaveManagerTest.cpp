#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/facade/DB.h>
#include <crepe/manager/SaveManager.h>

#include "ScriptTest.h"

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptSaveManagerTest : public ScriptTest {
public:
	class TestSaveManager : public SaveManager {
		using SaveManager::SaveManager;

		// in-memory database for testing
		DB db{};
		virtual DB & get_db() override { return this->db; }
	};

	TestSaveManager save_mgr{mediator};
};

TEST_F(ScriptSaveManagerTest, GetSaveManager) {
	MyScript & script = this->script;

	SaveManager & mgr = script.get_save_manager();

	EXPECT_EQ(&mgr, &save_mgr);
}
