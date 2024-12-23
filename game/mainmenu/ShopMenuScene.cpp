
#include "ShopMenuScene.h"
#include "api/Camera.h"
#include "MainMenuConfig.h"
#include "api/Sprite.h"
#include "BannerSubScene.h"

using namespace crepe;
using namespace std;

void ShopMenuScene::load_scene(){
	GameObject camera_object = this->new_object(MainMenuConfig::CAMERA_NAME);
	camera_object.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
	Camera::Data{
		.bg_color = Color::RED,
	});
	BannerSubScene banner;
	banner.create(*this);
	GameObject menu_background = this->new_object("menu_background");
	menu_background.add_component<Sprite>(
		Asset("asset/ui/background.png"),
		Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+0,
		.size = {1100,860},
		.position_offset {0},
		});
}

string ShopMenuScene::get_name() const { return "shopmenu"; }
