
#include "MainMenuScene.h"
#include "TransitionStartSubScript.h"
#include "MainMenuConfig.h"

#include "../ButtonSubScene.h"
#include "../MenusConfig.h"

#include "../../background/StartSubScene.h"
#include "../../background/HallwaySubScene.h"
#include "../../Config.h"

#include "../endgame/EndGameSubScene.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Camera.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;
using namespace std;

void MainMenuScene::load_scene(){
	ButtonSubScene button;

	GameObject camera_object = this->new_object(CAMERA_NAME);
	camera_object.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
	Camera::Data{
		.bg_color = Color::RED,
	});
	camera_object.add_component<BehaviorScript>().set_script<TransitionStartSubScript>();


	//Button menu
	GameObject menu_button = this->new_object(MENU_BUTTON_NAME,MENU_BUTTON_NAME,MENU_OFFSET);
	menu_button.add_component<Sprite>(
		Asset("asset/ui/background.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+0,
		.size = {300,860},
		.position_offset = MENU_OFFSET_BUTTON_BACKGROUND,
		});

	vec2 pos_btn = MENU_OFFSET_BUTTON;
	
	//Preview btn
	button.create(*this,ButtonSubScene::Data{
		.text = "PREVIEW",
		.text_width = 200,
		.position = pos_btn,
		.script_type = ButtonSubScene::ScriptSelect::PREVIEW,
	});

	//Shop btn
	pos_btn.y += MENU_BUTTON_SPACING + LARGE_OVERLAY_SIZE.y;
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
	HallwaySubScene hallway;
	float begin_x = start.create(*this, STARTMAP_OFFSET);
	begin_x = hallway.create(*this, begin_x, 1, Color::YELLOW);


	//INFO menu
	GameObject menu_info = this->new_object("MENU_INFO_BACKGROUND",MENU_INFO_TAG,MENU_OFFSET);
	menu_info.add_component<Sprite>(
		Asset("asset/ui/itemsButtonBlankDark.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+0,
		.size = {250,80},
		.position_offset = MENU_OFFSET_INFO,
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
		.position = MENU_OFFSET_INFO,
		.script_type = ButtonSubScene::ScriptSelect::SHOP,
		.scale = 0.6,
		.worldspace = false,
		.color_side = false,
		.tag = MENU_INFO_TAG,
	});

}

string MainMenuScene::get_name() const { return MAINMENU_SCENE; }
