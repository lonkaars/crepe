
#include "MainMenuScene.h"
#include "ButtonSubScene.h"
#include "TransitionStartScript.h"
#include "api/BehaviorScript.h"
#include "api/Camera.h"
#include "../background/StartSubScene.h"
#include "MainMenuConfig.h"
#include "api/GameObject.h"
#include "api/Sprite.h"
#include "manager/SaveManager.h"
#include "../Config.h"

using namespace crepe;
using namespace std;

void MainMenuScene::load_scene(){
	ButtonSubScene button;

	GameObject camera_object = this->new_object(MainMenuConfig::CAMERA_NAME);
	camera_object.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
	Camera::Data{
		.bg_color = Color::RED,
	});
	camera_object.add_component<BehaviorScript>().set_script<TransitionStartScript>();


	//Button menu
	GameObject menu_button = this->new_object(MainMenuConfig::MENU_BUTTON_NAME,MainMenuConfig::MENU_BUTTON_NAME,MainMenuConfig::MENU_OFFSET);
	menu_button.add_component<Sprite>(
		Asset("asset/ui/background.png"),
		Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+0,
		.size = {300,860},
		.position_offset = MainMenuConfig::MENU_OFFSET_BUTTON_BACKGROUND,
		});

	vec2 pos_btn = MainMenuConfig::MENU_OFFSET_BUTTON;
	
	//Preview btn
	button.create(*this,ButtonSubScene::Data{
		.text = "PREVIEW",
		.text_width = 200,
		.position = pos_btn,
		.script_type = ButtonSubScene::ScriptSelect::PREVIEW,
	});

	//Shop btn
	pos_btn.y += MainMenuConfig::MENU_BUTTON_SPACING + MainMenuConfig::LARGE_OVERLAY_SIZE.y;
	button.create(*this,ButtonSubScene::Data{
		.text = "SHOP",
		.text_offset = {-20,0},
		.text_width = 115,
		.icon_offset = {60,0},
		.icon_type = ButtonSubScene::IconSelect::SHOP,
		.position = pos_btn,
		.script_type = ButtonSubScene::ScriptSelect::SHOP,
	});
	
	//Start of map
	StartSubScene start;
	start.create(*this, MainMenuConfig::STARTMAP_OFFSET);

	//INFO menu
	GameObject menu_info = this->new_object("MENU_INFO_BACKGROUND",MainMenuConfig::MENU_INFO_TAG,MainMenuConfig::MENU_OFFSET);
	menu_info.add_component<Sprite>(
		Asset("asset/ui/itemsButtonBlankDark.png"),
		Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+0,
		.size = {250,80},
		.position_offset = MainMenuConfig::MENU_OFFSET_INFO,
		.world_space = false,
		});
	SaveManager & savemgr = this->get_save_manager();
	string number = std::to_string(savemgr.get<int>(TOTAL_COINS_GAME,0).get());
	float amount_number = static_cast<float>(number.size());
	// savemgr.set(COIN_GAME_AMOUNT, amount);
	button.create(*this,ButtonSubScene::Data{
		.text = number,
		.text_offset = {-10-(amount_number-1)*10,0},
		.text_width = amount_number*20,
		.icon_offset = {60,0},
		.icon_type = ButtonSubScene::IconSelect::COINS,
		.position = MainMenuConfig::MENU_OFFSET_INFO,
		.script_type = ButtonSubScene::ScriptSelect::SHOP,
		.scale = 0.6,
		.worldspace = false,
		.color_side = false,
		.tag = MainMenuConfig::MENU_INFO_TAG,
	});
	
}

string MainMenuScene::get_name() const { return "mainmenu"; }
