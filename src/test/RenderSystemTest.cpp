#include "api/Camera.h"
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#define private public
#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>

#include <crepe/system/RenderSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class RenderSystemTest : public Test {
public:
	ComponentManager mgr{};
	RenderSystem sys{mgr};
	GameObject entity1 = this->mgr.new_object("name");
	GameObject entity2 = this->mgr.new_object("name");
	GameObject entity3 = this->mgr.new_object("name");
	GameObject entity4 = this->mgr.new_object("name");

	void SetUp() override {
		auto & sprite1
			= entity1.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		ASSERT_NE(sprite1.sprite_image.get(), nullptr);
		sprite1.order_in_layer = 5;
		sprite1.sorting_in_layer = 5;
		EXPECT_EQ(sprite1.order_in_layer, 5);
		EXPECT_EQ(sprite1.sorting_in_layer, 5);
		auto & sprite2
			= entity2.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		ASSERT_NE(sprite2.sprite_image.get(), nullptr);
		sprite2.sorting_in_layer = 2;
		sprite2.order_in_layer = 1;

		EXPECT_EQ(sprite2.sorting_in_layer, 2);
		EXPECT_EQ(sprite2.order_in_layer, 1);

		auto & sprite3
			= entity3.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		ASSERT_NE(sprite3.sprite_image.get(), nullptr);
		sprite3.sorting_in_layer = 1;
		sprite3.order_in_layer = 2;

		EXPECT_EQ(sprite3.sorting_in_layer, 1);
		EXPECT_EQ(sprite3.order_in_layer, 2);

		auto & sprite4
			= entity4.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		ASSERT_NE(sprite4.sprite_image.get(), nullptr);
		sprite4.sorting_in_layer = 1;
		sprite4.order_in_layer = 1;
		EXPECT_EQ(sprite4.sorting_in_layer, 1);
		EXPECT_EQ(sprite4.order_in_layer, 1);
	}
};

TEST_F(RenderSystemTest, expected_throws) {
	GameObject entity1 = this->mgr.new_object("NAME");

	// no texture img
	EXPECT_ANY_THROW({
		entity1.add_component<Sprite>(make_shared<Texture>("NO_IMAGE"), Color(0, 0, 0, 0),
									  FlipSettings{false, false});
	});

	// No camera
	EXPECT_ANY_THROW({ this->sys.update(); });
}

TEST_F(RenderSystemTest, make_sprites) {}

TEST_F(RenderSystemTest, sorting_sprites) {
	vector<reference_wrapper<Sprite>> sprites = this->mgr.get_components_by_type<Sprite>();
	ASSERT_EQ(sprites.size(), 4);

	vector<reference_wrapper<Sprite>> sorted_sprites = this->sys.sort(sprites);
	ASSERT_EQ(sorted_sprites.size(), 4);

	// Expected order after sorting:
	// 1. sorting_in_layer: 1, order_in_layer: 1 (entity4)
	// 2. sorting_in_layer: 1, order_in_layer: 2 (entity3)
	// 3. sorting_in_layer: 2, order_in_layer: 1 (entity2)
	// 4. sorting_in_layer: 5, order_in_layer: 5 (entity1)

	EXPECT_EQ(sorted_sprites[0].get().sorting_in_layer, 1);
	EXPECT_EQ(sorted_sprites[0].get().order_in_layer, 1);

	EXPECT_EQ(sorted_sprites[1].get().sorting_in_layer, 1);
	EXPECT_EQ(sorted_sprites[1].get().order_in_layer, 2);

	EXPECT_EQ(sorted_sprites[2].get().sorting_in_layer, 2);
	EXPECT_EQ(sorted_sprites[2].get().order_in_layer, 1);

	EXPECT_EQ(sorted_sprites[3].get().sorting_in_layer, 5);
	EXPECT_EQ(sorted_sprites[3].get().order_in_layer, 5);

	for (size_t i = 1; i < sorted_sprites.size(); ++i) {
		const Sprite & prev = sorted_sprites[i - 1].get();
		const Sprite & curr = sorted_sprites[i].get();

		if (prev.sorting_in_layer == curr.sorting_in_layer) {
			EXPECT_LE(prev.order_in_layer, curr.order_in_layer);
		} else {
			EXPECT_LE(prev.sorting_in_layer, curr.sorting_in_layer);
		}
	}
}

TEST_F(RenderSystemTest, Update) {
	entity1.add_component<Camera>(Color::WHITE);
	{
		vector<reference_wrapper<Sprite>> sprites = this->mgr.get_components_by_type<Sprite>();
		ASSERT_EQ(sprites.size(), 4);

		EXPECT_EQ(sprites[0].get().game_object_id, 0);
		EXPECT_EQ(sprites[1].get().game_object_id, 1);
		EXPECT_EQ(sprites[2].get().game_object_id, 2);
		EXPECT_EQ(sprites[3].get().game_object_id, 3);
	}
	this->sys.update();
	{
		vector<reference_wrapper<Sprite>> sprites = this->mgr.get_components_by_type<Sprite>();
		ASSERT_EQ(sprites.size(), 4);

		EXPECT_EQ(sprites[0].get().game_object_id, 0);
		EXPECT_EQ(sprites[1].get().game_object_id, 1);
		EXPECT_EQ(sprites[2].get().game_object_id, 2);
		EXPECT_EQ(sprites[3].get().game_object_id, 3);
	}
}

TEST_F(RenderSystemTest, Camera) {
	{
		auto cameras = this->mgr.get_components_by_type<Camera>();
		EXPECT_NE(cameras.size(), 1);
	}
	{
		entity1.add_component<Camera>(Color::WHITE);
		auto cameras = this->mgr.get_components_by_type<Camera>();
		EXPECT_EQ(cameras.size(), 1);
	}

	//TODO improve with newer version
}
TEST_F(RenderSystemTest, Color) {
	entity1.add_component<Camera>(Color::WHITE);
	auto & sprite = this->mgr.get_components_by_id<Sprite>(entity1.id).front().get();
	ASSERT_NE(sprite.sprite_image.get(), nullptr);

	sprite.color = Color::GREEN;
	EXPECT_EQ(sprite.color.r, Color::GREEN.r);
	EXPECT_EQ(sprite.color.g, Color::GREEN.g);
	EXPECT_EQ(sprite.color.b, Color::GREEN.b);
	EXPECT_EQ(sprite.color.a, Color::GREEN.a);
	this->sys.update();
	EXPECT_EQ(sprite.color.r, Color::GREEN.r);
	EXPECT_EQ(sprite.color.g, Color::GREEN.g);
	EXPECT_EQ(sprite.color.b, Color::GREEN.b);
	EXPECT_EQ(sprite.color.a, Color::GREEN.a);
}
