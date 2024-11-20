#include <gtest/gtest.h>

#include <crepe/ValueBroker.h>
#include <crepe/util/Proxy.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ValueBrokerTest : public Test {
public:
	int read_count = 0;
	int write_count = 0;
	int value = 0;

	ValueBroker<int> broker {
		[this](const int & target) -> void {
			this->write_count++;
			this->value = target;
		},
		[this]() -> const int & {
			this->read_count++;
			return this->value;
		},
	};
	Proxy<int> proxy{broker};

	void SetUp() override {
		ASSERT_EQ(read_count, 0);
		ASSERT_EQ(write_count, 0);
	}
};

TEST_F(ValueBrokerTest, BrokerWrite) {
	broker.set(0);
	EXPECT_EQ(read_count, 0);
	EXPECT_EQ(write_count, 1);
}

TEST_F(ValueBrokerTest, BrokerRead) {
	broker.get();
	EXPECT_EQ(read_count, 1);
	EXPECT_EQ(write_count, 0);
}

TEST_F(ValueBrokerTest, ProxyWrite) {
	proxy = 0;
	EXPECT_EQ(read_count, 0);
	EXPECT_EQ(write_count, 1);
}

void dummy(int) { }
TEST_F(ValueBrokerTest, ProxyRead) {
	dummy(proxy);
	EXPECT_EQ(read_count, 1);
	EXPECT_EQ(write_count, 0);
}

TEST_F(ValueBrokerTest, ProxyReadWrite) {
	proxy = proxy;
	ASSERT_EQ(read_count, 1);
	ASSERT_EQ(write_count, 1);
}

