#include <gtest/gtest.h>

#define private public
#define protected public

#include <crepe/util/Log.h>
#include <crepe/manager/ResourceManager.h>
#include <crepe/api/GameObject.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ResourceManagerTest : public Test {
	Mediator mediator;
public:
	ResourceManager resource_manager{mediator};

	Asset asset_a{"asset/texture/img.png"};
	Asset asset_b{"asset/texture/ERROR.png"};

	class TestResource : public Resource {
	public:
		static unsigned instances;

	public:
		const unsigned instance;
		TestResource(const Asset & src)
			: Resource(src),
				instance(this->instances++) { }
		~TestResource() { this->instances--; }
		bool operator == (const TestResource & other) const {
			return this->instance == other.instance;
		}
	};

private:
	void SetUp() override {
		TestResource::instances = 0;
	}
};
unsigned ResourceManagerTest::TestResource::instances = 0;

TEST_F(ResourceManagerTest, Default) {
	TestResource & res_1 = resource_manager.get<TestResource>(asset_a);
	TestResource & res_2 = resource_manager.get<TestResource>(asset_a);
	TestResource & res_3 = resource_manager.get<TestResource>(asset_b);
	TestResource & res_4 = resource_manager.get<TestResource>(asset_b);

	ASSERT_EQ(res_1, res_2);
	ASSERT_EQ(res_3, res_4);
	EXPECT_NE(res_1, res_3);

	EXPECT_EQ(TestResource::instances, 2);

	resource_manager.clear();
}

TEST_F(ResourceManagerTest, Persistent) {
	resource_manager.set_persistent(asset_a, true);
	EXPECT_EQ(TestResource::instances, 0);

	resource_manager.get<TestResource>(asset_a);
	resource_manager.get<TestResource>(asset_a);
	resource_manager.get<TestResource>(asset_b);
	resource_manager.get<TestResource>(asset_b);
	EXPECT_EQ(TestResource::instances, 2);

	resource_manager.clear();
	EXPECT_EQ(TestResource::instances, 1);

	resource_manager.clear_all();
	EXPECT_EQ(TestResource::instances, 0);
}

