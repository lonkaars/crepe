#include <gtest/gtest.h>

#include <crepe/ValueBroker.h>
#include <crepe/facade/DB.h>
#include <crepe/manager/SaveManager.h>

using namespace std;
using namespace crepe;
using namespace testing;

class SaveManagerTest : public Test {
	Mediator m;
	class TestSaveManager : public SaveManager {
		using SaveManager::SaveManager;

		// in-memory database for testing
		DB db{};
		virtual DB & get_db() override { return this->db; }
	};

public:
	TestSaveManager mgr{m};
};

TEST_F(SaveManagerTest, ReadWrite) {
	ASSERT_FALSE(mgr.has("foo"));
	mgr.set<string>("foo", "bar");
	ASSERT_TRUE(mgr.has("foo"));

	string value = mgr.get<string>("foo");
	EXPECT_EQ(value, "bar");
}

TEST_F(SaveManagerTest, DefaultValue) {
	ValueBroker value = mgr.get<int>("foo", 3);

	ASSERT_EQ(value.get(), 3);
	value.set(5);
	ASSERT_EQ(value.get(), 5);
}
