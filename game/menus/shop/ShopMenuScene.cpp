
#include "ShopMenuScene.h"

#include "../../Config.h"
#include "../ButtonSubScene.h"
#include "../MenusConfig.h"
#include "api/BehaviorScript.h"
#include "menus/BannerSubScene.h"
#include "menus/shop/ShopLoadScript.h"
#include "types.h"

#include "Shopconfig.h"
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
	menu_background.add_component<BehaviorScript>().set_script<ShopLoadScript>();

	ButtonSubScene button;
	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "BACK",
			.text_width = 115,
			.position = {-400, -350},
			.script_type = ButtonSubScene::ScriptSelect::MAINMENU,
			.button_type = ButtonSubScene::ButtonSelect::BACK,
			.scale = 0.8,
			.sorting_layer_offset = 1,
		}
	);

	const float CHAR_SIZE = 16;
	const float CHAR_SIZE_COIN = 16;
	crepe::vec2 size;

	GameObject shop_item_bullet = this->new_object("bullet", "shop_item", vec2(-100, 0));
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.angle_offset = 30,
			.position_offset = {0, 0},
		}
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.angle_offset = 10,
			.position_offset = {-10, -30},
		}
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.angle_offset = -10,
			.position_offset = {-40, 30},
		}
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.angle_offset = 0,
			.position_offset = {10, 15},
		}
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/other_effects/effect_rocketmgshell_TVOS.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.angle_offset = -5,
			.position_offset = {45, -5},
		}
	);

	const string BULLETS_STRING = "BULLETS";
	size
		= {CHAR_SIZE * BULLETS_STRING.size(),
		   (CHAR_SIZE * BULLETS_STRING.size() / BULLETS_STRING.size()) * 2};

	shop_item_bullet.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::WHITE,
		},
		vec2 {0, -75}, BULLETS_STRING
	);
	shop_item_bullet.add_component<Sprite>(
		Asset("asset/ui/buttonCoinsSmall.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 45},
			.position_offset = {25, 75},
		}
	);

	const string BULLETS_GOLD_STRING = "0";
	size
		= {CHAR_SIZE_COIN * BULLETS_GOLD_STRING.size(),
		   (CHAR_SIZE_COIN * BULLETS_GOLD_STRING.size() / BULLETS_GOLD_STRING.size()) * 2};
	shop_item_bullet.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::GOLD,
		},
		vec2 {-5, 75}, BULLETS_GOLD_STRING
	);

	GameObject shop_item_bubble = this->new_object("bubble", "shop_item", vec2(100, 0));
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 10},
			.position_offset = {0, 0},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 10},
			.position_offset = {-50, -20},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.position_offset = {45, -40},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.position_offset = {-20, 40},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 15},
			.position_offset = {15, -25},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 10},
			.position_offset = {10, 5},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 10},
			.position_offset = {-5, -20},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.position_offset = {15, -40},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 20},
			.position_offset = {-20, 10},
		}
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/background/aquarium/bubble.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 15},
			.position_offset = {30, -25},
		}
	);

	const string BUBBLE_STRING = "BUBBLE";
	size
		= {CHAR_SIZE * BUBBLE_STRING.size(),
		   (CHAR_SIZE * BUBBLE_STRING.size() / BUBBLE_STRING.size()) * 2};
	shop_item_bubble.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::WHITE,
		},
		vec2 {0, -75}, BUBBLE_STRING
	);
	shop_item_bubble.add_component<Sprite>(
		Asset("asset/ui/buttonCoinsSmall.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {0, 45},
			.position_offset = {45, 75},
		}
	);

	const string BUBBLE_GOLD_STRING = "1000";
	size
		= {CHAR_SIZE_COIN * BUBBLE_GOLD_STRING.size(),
		   (CHAR_SIZE_COIN * BUBBLE_GOLD_STRING.size() / BUBBLE_GOLD_STRING.size()) * 2};
	shop_item_bubble.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::GOLD,
		},
		vec2 {-10, 75}, BUBBLE_GOLD_STRING
	);

	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "BUY",
			.text_width = 100,
			.position = vec2(-100, 120),
			.script_type = ButtonSubScene::ScriptSelect::SHOP_BULLET,
			.button_type = ButtonSubScene::ButtonSelect::LARGE,
			.scale = 0.4,
			.tag = BUY_BULLET,
			.sorting_layer_offset = 20,
			.btn_side_color = ButtonSubScene::ButtonSideColor::PURPLE

		}
	);

	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "BUY",
			.text_width = 100,
			.position = vec2(100, 120),
			.script_type = ButtonSubScene::ScriptSelect::SHOP_BUBBLE,
			.button_type = ButtonSubScene::ButtonSelect::LARGE,
			.scale = 0.4,
			.tag = BUY_BUBBLE,
			.sorting_layer_offset = 20,
			.btn_side_color = ButtonSubScene::ButtonSideColor::PURPLE
		}
	);

	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "SELECT",
			.text_width = 100,
			.position = vec2(-100, 120),
			.script_type = ButtonSubScene::ScriptSelect::SHOP_BULLET,
			.button_type = ButtonSubScene::ButtonSelect::LARGE,
			.scale = 0.4,
			.tag = SELECT_BULLET,
			.sorting_layer_offset = 20,
			.btn_side_color = ButtonSubScene::ButtonSideColor::PURPLE
		}
	);

	button.create(
		*this,
		ButtonSubScene::Data {
			.text = "SELECT",
			.text_width = 100,
			.position = vec2(100, 120),
			.script_type = ButtonSubScene::ScriptSelect::SHOP_BUBBLE,
			.button_type = ButtonSubScene::ButtonSelect::LARGE,
			.scale = 0.4,
			.tag = SELECT_BUBBLE,
			.sorting_layer_offset = 20,
			.btn_side_color = ButtonSubScene::ButtonSideColor::PURPLE
		}
	);
}

string ShopMenuScene::get_name() const { return SHOP_SCENE; }
