#include <gtest/gtest.h>

#include <crepe/facade/DB.h>

using namespace std;
using namespace crepe;
using namespace testing;

class DBTest : public Test {
public:
	DB db;
};

TEST_F(DBTest, ReadWrite) {
	db.set("foo", "bar");
	EXPECT_EQ(db.get("foo"), "bar");
}

TEST_F(DBTest, Nonexistant) {
	EXPECT_THROW(db.get("foo"), std::out_of_range);
	db.set("foo", "bar");
	EXPECT_NO_THROW(db.get("foo"));
}

TEST_F(DBTest, Has) {
	EXPECT_EQ(db.has("foo"), false);
	db.set("foo", "bar");
	EXPECT_EQ(db.has("foo"), true);
}

TEST_F(DBTest, MultipleKeys) {
	db.set("foo", "foo");
	db.set("bar", "bar");

	EXPECT_EQ(db.get("foo"), "foo");
	EXPECT_EQ(db.get("bar"), "bar");
}
