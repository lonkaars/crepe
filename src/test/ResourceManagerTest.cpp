#include <gtest/gtest.h>

#define private public
#define protected public

#include <crepe/util/Log.h>
#include <crepe/ResourceManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>

using namespace std;
using namespace crepe;
using namespace testing;

class TestComponent : public Component {
public:
	TestComponent(game_object_id_t id, const Asset & asset)
		: Component(id),
		  source(asset) {}
	const Asset source;
};

class TestResource : public Resource {
public:
	static unsigned instances;

public:
	const unsigned instance;
	TestResource(const Asset & src)
		: Resource(src),
		  instance(this->instances++) { }
};
unsigned TestResource::instances = 0;

template <>
TestResource & ResourceManager::get(const TestComponent & component) {
	return this->get_internal<TestResource>(component, component.source);
}

class ResourceManagerTest : public Test {
public:
	ResourceManager resource_manager{};

	static constexpr const char * ASSET_LOCATION = "asset/texture/img.png";

	TestComponent a{0, ASSET_LOCATION};
	TestComponent b{1, ASSET_LOCATION};

private:
	void SetUp() override {
		TestResource::instances = 0;
	}
};

TEST_F(ResourceManagerTest, Uncached) {
	TestResource & res_1 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_2 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_3 = resource_manager.get<TestResource>(b); // 2
	TestResource & res_4 = resource_manager.get<TestResource>(b); // 2

	ASSERT_EQ(res_1, res_2);
	ASSERT_EQ(res_3, res_4);
	EXPECT_NE(res_1, res_3);

	EXPECT_EQ(TestResource::instances, 2);
}

// TODO: per GameObject / Component
TEST_F(ResourceManagerTest, PerComponent) {
	resource_manager.cache(a);
	resource_manager.cache(b);

	TestResource & res_1 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_2 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_3 = resource_manager.get<TestResource>(b); // 2
	TestResource & res_4 = resource_manager.get<TestResource>(b); // 2

	ASSERT_EQ(res_1, res_2);
	ASSERT_EQ(res_3, res_4);
	EXPECT_NE(res_1, res_3);

	EXPECT_EQ(TestResource::instances, 2);
}

TEST_F(ResourceManagerTest, PerAsset) {
	resource_manager.cache(ASSET_LOCATION);
	EXPECT_EQ(TestResource::instances, 1);

	TestResource & res_1 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_2 = resource_manager.get<TestResource>(a); // 1
	TestResource & res_3 = resource_manager.get<TestResource>(b); // 1
	TestResource & res_4 = resource_manager.get<TestResource>(b); // 1

	EXPECT_EQ(res_1, res_2);
	EXPECT_EQ(res_2, res_3);
	EXPECT_EQ(res_3, res_4);

	EXPECT_EQ(TestResource::instances, 1);
}

