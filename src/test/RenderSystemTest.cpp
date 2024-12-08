#include "api/Asset.h"
#include "facade/SDLContext.h"
#include "manager/ResourceManager.h"
#include "types.h"
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#define private public
#define protected public

#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/manager/ComponentManager.h>

#include <crepe/system/RenderSystem.h>

using namespace std;
using namespace crepe;
using namespace testing;

class RenderSystemTest : public Test {
	Mediator m;

public:
	ComponentManager mgr{m};
	SDLContext ctx{m};
	ResourceManager resource_manager{m};
	RenderSystem sys{m};
	GameObject entity1 = this->mgr.new_object("name");
	GameObject entity2 = this->mgr.new_object("name");
	GameObject entity3 = this->mgr.new_object("name");
	GameObject entity4 = this->mgr.new_object("name");

	void SetUp() override {
		auto s1 = Asset("asset/texture/img.png");
		auto s2 = Asset("asset/texture/img.png");
		auto s3 = Asset("asset/texture/img.png");
		auto s4 = Asset("asset/texture/img.png");
		auto & sprite1
			= entity1.add_component<Sprite>(s1, Sprite::Data{
													.color = Color(0, 0, 0, 0),
													.flip = Sprite::FlipSettings{false, false},
													.sorting_in_layer = 5,
													.order_in_layer = 5,
													.size = {10, 10},
												});

		//ASSERT_NE(sprite1.texture.texture.get(), nullptr);
		EXPECT_EQ(sprite1.data.order_in_layer, 5);
		EXPECT_EQ(sprite1.data.sorting_in_layer, 5);
		auto & sprite2
			= entity2.add_component<Sprite>(s2, Sprite::Data{
													.color = Color(0, 0, 0, 0),
													.flip = Sprite::FlipSettings{false, false},
													.sorting_in_layer = 2,
													.order_in_layer = 1,
												});
		//ASSERT_NE(sprite2.texture.texture.get(), nullptr);
		EXPECT_EQ(sprite2.data.sorting_in_layer, 2);
		EXPECT_EQ(sprite2.data.order_in_layer, 1);

		auto & sprite3
			= entity3.add_component<Sprite>(s3, Sprite::Data{
													.color = Color(0, 0, 0, 0),
													.flip = Sprite::FlipSettings{false, false},
													.sorting_in_layer = 1,
													.order_in_layer = 2,
												});
		//ASSERT_NE(sprite3.texture.texture.get(), nullptr);
		EXPECT_EQ(sprite3.data.sorting_in_layer, 1);
		EXPECT_EQ(sprite3.data.order_in_layer, 2);

		auto & sprite4
			= entity4.add_component<Sprite>(s4, Sprite::Data{
													.color = Color(0, 0, 0, 0),
													.flip = Sprite::FlipSettings{false, false},
													.sorting_in_layer = 1,
													.order_in_layer = 1,
												});
		//ASSERT_NE(sprite4.texture.texture.get(), nullptr);
		EXPECT_EQ(sprite4.data.sorting_in_layer, 1);
		EXPECT_EQ(sprite4.data.order_in_layer, 1);
	}
};

TEST_F(RenderSystemTest, expected_throws) {
	GameObject entity1 = this->mgr.new_object("NAME");

	// no texture img
	EXPECT_NO_THROW({
		auto test = Asset("");
		auto & sprite1 = entity1.add_component<Sprite>(
			test, Sprite::Data{
					  .color = Color(0, 0, 0, 0),
					  .flip = Sprite::FlipSettings{false, false},
					  .sorting_in_layer = 1,
					  .order_in_layer = 1,
				  });
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

	EXPECT_EQ(sorted_sprites[0].get().data.sorting_in_layer, 1);
	EXPECT_EQ(sorted_sprites[0].get().data.order_in_layer, 1);

	EXPECT_EQ(sorted_sprites[1].get().data.sorting_in_layer, 1);
	EXPECT_EQ(sorted_sprites[1].get().data.order_in_layer, 2);

	EXPECT_EQ(sorted_sprites[2].get().data.sorting_in_layer, 2);
	EXPECT_EQ(sorted_sprites[2].get().data.order_in_layer, 1);

	EXPECT_EQ(sorted_sprites[3].get().data.sorting_in_layer, 5);
	EXPECT_EQ(sorted_sprites[3].get().data.order_in_layer, 5);

	for (size_t i = 1; i < sorted_sprites.size(); ++i) {
		const Sprite & prev = sorted_sprites[i - 1].get();
		const Sprite & curr = sorted_sprites[i].get();

		if (prev.data.sorting_in_layer == curr.data.sorting_in_layer) {
			EXPECT_LE(prev.data.order_in_layer, curr.data.order_in_layer);
		} else {
			EXPECT_LE(prev.data.sorting_in_layer, curr.data.sorting_in_layer);
		}
	}
}

TEST_F(RenderSystemTest, Update) {
	entity1.add_component<Camera>(ivec2{100, 100}, vec2{100, 100},
								  Camera::Data{.bg_color = Color::WHITE, .zoom = 1.0f});
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
		entity1.add_component<Camera>(ivec2{100, 100}, vec2{100, 100},
									  Camera::Data{.bg_color = Color::WHITE, .zoom = 1.0f});

		auto cameras = this->mgr.get_components_by_type<Camera>();
		EXPECT_EQ(cameras.size(), 1);
	}

	//TODO improve with newer version
}
TEST_F(RenderSystemTest, Color) {
	entity1.add_component<Camera>(ivec2{100, 100}, vec2{100, 100},
								  Camera::Data{.bg_color = Color::WHITE, .zoom = 1.0f});

	auto & sprite = this->mgr.get_components_by_id<Sprite>(entity1.id).front().get();
	//ASSERT_NE(sprite.texture.texture.get(), nullptr);

	sprite.data.color = Color::GREEN;
	EXPECT_EQ(sprite.data.color.r, Color::GREEN.r);
	EXPECT_EQ(sprite.data.color.g, Color::GREEN.g);
	EXPECT_EQ(sprite.data.color.b, Color::GREEN.b);
	EXPECT_EQ(sprite.data.color.a, Color::GREEN.a);
	this->sys.update();
	EXPECT_EQ(sprite.data.color.r, Color::GREEN.r);
	EXPECT_EQ(sprite.data.color.g, Color::GREEN.g);
	EXPECT_EQ(sprite.data.color.b, Color::GREEN.b);
	EXPECT_EQ(sprite.data.color.a, Color::GREEN.a);
}
