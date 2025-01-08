
#include "ShopMenuScene.h"

#include "../../Config.h"
#include "../BannerSubScene.h"
#include "../ButtonSubScene.h"
#include "../MenusConfig.h"
#include "types.h"

#include <crepe/api/Camera.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>

using namespace crepe;
using namespace std;

void ShopMenuScene::load_scene() {
	GameObject camera_object = this->new_object(CAMERA_NAME);
	camera_object.add_component<Camera>(
		ivec2(990, 720), vec2(1100, 800),
		Camera::Data {
			.bg_color = Color::RED,
		}
	);
	BannerSubScene banner;
	banner.create(
		*this,
		{
			.banner_title = "SHOP",
			.banner_title_width = 200,
			.banner_title_offset = {0, 65},
		}
	);
	GameObject menu_background = this->new_object("menu_background");
	menu_background.add_component<Sprite>(
		Asset("asset/ui/background.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 0,
			.size = {1100, 860},
			.position_offset {0},
		}
	);

	ButtonSubScene button;
	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "BACK",
			.text_width = 115,
			.position = {-400, -350},
			.script_type = ButtonSubScene::ScriptSelect::MAINMENU,
			.button_type = ButtonSubScene::ButtonSelect::BACK,
			.scale = 0.8
		}
	);

	GameObject shop_item_bullet = this->new_object("bullet", "shop_item", vec2(-100, 0));
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 100},
			.position_offset = {0, 0},
		}
	);
	shop_item_bullet.add_component<Text>(
		vec2 {100, 50}, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::WHITE,
		},
		vec2 {0, -75}, "BULLETS"
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/ui/buttonCoinsSmall.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 45},
			.position_offset = {25, 75},
		}
	);
	shop_item_bullet.add_component<Text>(
		vec2 {37.5, 37.5}, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::YELLOW,
		},
		vec2 {-25, 75}, "0"
	);

	GameObject shop_item_bubble = this->new_object("bubble", "shop_item", vec2(100, 0));
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 100},
			.position_offset = {0, 0},
		}
	);
	shop_item_bubble.add_component<Text>(
		vec2 {100, 50}, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::WHITE,
		},
		vec2 {0, -75}, "BUBBLE"
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/ui/buttonCoinsSmall.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 45},
			.position_offset = {45, 75},
		}
	);
	shop_item_bubble.add_component<Text>(
		vec2 {100, 25}, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::YELLOW,
		},
		vec2 {-25, 75}, "1000"
	);
}

string ShopMenuScene::get_name() const { return SHOP_SCENE; }
