
#include "ShopMenuScene.h"

#include "../BannerSubScene.h"
#include "../ButtonSubScene.h"
#include "../MenusConfig.h"

#include <crepe/api/Camera.h>
#include <crepe/api/Sprite.h>

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

	//
}

string ShopMenuScene::get_name() const { return SHOP_SCENE; }
