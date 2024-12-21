
#include "MainMenuScene.h"
#include "ButtonSubScene.h"
#include "api/Camera.h"
#include "../StartSubScene.h"
#include "MainMenuConfig.h"
#include "api/GameObject.h"
#include "api/Rigidbody.h"
#include "api/Sprite.h"

using namespace crepe;
using namespace std;

void MainMenuScene::load_scene(){
	GameObject camera_object = this->new_object(MainMenuConfig::CAMERA_NAME);
	camera_object.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
	Camera::Data{
		.bg_color = Color::RED,
	});

	GameObject menu_background = this->new_object("menu_background","",MainMenuConfig::MENU_OFFSET + MainMenuConfig::MENU_OFFSET_BACKGROUND);
	menu_background.add_component<Sprite>(
		Asset("asset/ui/itemsButtonBlankDark.png"),
		Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+0,
		.size = {300,922},
		});
	
	ButtonSubScene button;
	vec2 pos = MainMenuConfig::MENU_OFFSET;
	
	//Start btn
	button.create(*this,ButtonSubScene::Data{
		.text = "START",
		.text_size = vec2{200,80},
		.position = pos,
		.script = ButtonSubScene::ScriptSelect::START,
	});
	
	//Preview btn
	pos.y += MainMenuConfig::MENU_BUTTON_SPACING + MainMenuConfig::LARGE_OVERLAY_SIZE.y;
	button.create(*this,ButtonSubScene::Data{
		.text = "PREVIEW",
		.text_size = vec2{200,80},
		.position = pos,
		.script = ButtonSubScene::ScriptSelect::PREVIEW,
	});

	//Shop btn
	// pos.y += MainMenuConfig::MENU_BUTTON_SPACING + MainMenuConfig::LARGE_OVERLAY_SIZE.y;
	// button.create(*this,"SHOP",vec2{0,0},vec2{200,80},pos);
	
	//Start of map
	StartSubScene start;
	start.create(*this, MainMenuConfig::STARTMAP_OFFSET);
}

string MainMenuScene::get_name() const { return "mainmenu"; }
