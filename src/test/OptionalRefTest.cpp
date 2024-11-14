#include <gtest/gtest.h>

#include <crepe/util/OptionalRef.h>

using namespace std;
using namespace crepe;
using namespace testing;

TEST(OptionalRefTest, Explicit) {
	string value = "foo";
	OptionalRef<string> ref;

	EXPECT_FALSE(bool(ref));
	ASSERT_THROW(ref.get(), runtime_error);
}

