#include <gtest/gtest.h>

#include <crepe/util/OptionalRef.h>

using namespace std;
using namespace crepe;
using namespace testing;

TEST(OptionalRefTest, Normal) {
	string value = "foo";
	OptionalRef<string> ref = value;

	EXPECT_TRUE(ref);
	ASSERT_NO_THROW({
		string & value_ref = ref;
		EXPECT_EQ(value_ref, value);
	});

	ref.clear();
	EXPECT_FALSE(ref);
	ASSERT_THROW({
		string & value_ref = ref;
	}, runtime_error);
}

TEST(OptionalRefTest, Empty) {
	string value = "foo";
	OptionalRef<string> ref;

	EXPECT_FALSE(ref);
	ASSERT_THROW({
		string & value_ref = ref;
	}, runtime_error);
}

TEST(OptionalRefTest, Chain) {
	string value = "foo";
	OptionalRef<string> ref1 = value;
	OptionalRef<string> ref2 = ref1;

	EXPECT_TRUE(ref2);
	string & value_ref = ref2;
	EXPECT_EQ(value_ref, value);
	value_ref = "bar";
	EXPECT_EQ(value_ref, value);
}

