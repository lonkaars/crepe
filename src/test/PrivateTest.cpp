#include <gtest/gtest.h>

#include <crepe/util/Private.h>

using namespace std;
using namespace crepe;
using namespace testing;

class PrivateTest : public Test {
public:
	static unsigned constructors;
	static unsigned destructors;

	void SetUp() override {
		PrivateTest::constructors = 0;
		PrivateTest::destructors = 0;
	}

	class TestClass {
	public:
		TestClass() { PrivateTest::constructors++; }
		~TestClass() { PrivateTest::destructors++; }
	};
	class Unrelated {};
};
unsigned PrivateTest::constructors;
unsigned PrivateTest::destructors;

TEST_F(PrivateTest, Empty) {
	{
		Private foo;
	}

	EXPECT_EQ(PrivateTest::constructors, 0);
	EXPECT_EQ(PrivateTest::destructors, 0);
}

TEST_F(PrivateTest, WithObject) {
	{
		Private foo;
		foo.set<TestClass>();

		EXPECT_EQ(PrivateTest::constructors, 1);
		EXPECT_EQ(PrivateTest::destructors, 0);
	}

	EXPECT_EQ(PrivateTest::constructors, 1);
	EXPECT_EQ(PrivateTest::destructors, 1);
}

TEST_F(PrivateTest, EmptyException) {
	Private foo;
	EXPECT_THROW(foo.get<TestClass>(), std::out_of_range);

	foo.set<TestClass>();
	EXPECT_NO_THROW(foo.get<TestClass>());
}

TEST_F(PrivateTest, IncorrectTypeException) {
	Private foo;
	foo.set<TestClass>();

	EXPECT_THROW(foo.get<Unrelated>(), std::logic_error);
	EXPECT_NO_THROW(foo.get<TestClass>());
}

