#include <gtest/gtest.h>

#include <crepe/util/OptionalRef.h>

using namespace std;
using namespace crepe;
using namespace testing;

TEST(OptionalRefTest, Explicit) {
	string value = "foo";
	OptionalRef<string> ref;
	EXPECT_FALSE(ref);
	ASSERT_THROW(ref.get(), runtime_error);

	ref.set(value);
	EXPECT_TRUE(ref);
	ASSERT_NO_THROW(ref.get());

	ref.clear();
	EXPECT_FALSE(ref);
	ASSERT_THROW(ref.get(), runtime_error);
}

TEST(OptionalRefTest, Implicit) {
	string value = "foo";
	OptionalRef<string> ref = value;
	EXPECT_TRUE(ref);
	ASSERT_NO_THROW(ref.get());

	ref.clear();
	EXPECT_FALSE(ref);
	ASSERT_THROW(ref.get(), runtime_error);

	ref = value;
	EXPECT_TRUE(ref);
	ASSERT_NO_THROW(ref.get());
}

