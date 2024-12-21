#include "ButtonSubScene.h"
#include "ButtonScript.h"
#include "ButtonStartScript.h"
#include "MainMenuConfig.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Button.h>
#include <crepe/api/Text.h>

using namespace crepe;
using namespace std;

void ButtonSubScene::create(Scene & scn,const Data & data){
	GameObject button_object = scn.new_object("button","",data.position,0,1);
	this->large_btn_overlay(button_object);
	this->btn_text_middle(button_object,data.text,data.text_offset,data.text_size);
	this->set_script(button_object,data.script);
}
void ButtonSubScene::large_btn_overlay(crepe::GameObject & button_object){
	button_object.add_component<Sprite>(Asset("asset/ui/buttonBacking.png"),Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+1,
		.size = MainMenuConfig::LARGE_OVERLAY_SIZE,
	});
	button_object.add_component<Button>(MainMenuConfig::LARGE_OVERLAY_SIZE,vec2{0,0});
	this->btn_color_side(button_object,SIDE_PANEL_OFFSET);
}

void ButtonSubScene::btn_color_side(crepe::GameObject & button_object,const vec2 & offset){
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+2,
		.size = MainMenuConfig::SIDE_PANEL_SIZE,
		.position_offset = offset,
	});
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.flip = {true,false},
		.sorting_in_layer = MainMenuConfig::STARTING_SORTING_IN_LAYER+2,
		.size = MainMenuConfig::SIDE_PANEL_SIZE,
		.position_offset = {-offset.x,offset.y},
	});
}

//fc-match arial
void ButtonSubScene::btn_text_middle(crepe::GameObject & button_object,const std::string & text,const crepe::vec2 & text_offset,const crepe::vec2 & text_size){
	button_object.add_component<Text>(text_size,text_offset+MainMenuConfig::FONTOFFSET, MainMenuConfig::FONT, Text::Data{
		.text_color = Color::WHITE,
		}, text);
}

void ButtonSubScene::set_script(crepe::GameObject & button_object,ScriptSelect script){
	switch (script) {
		case ScriptSelect::START:
			button_object.add_component<BehaviorScript>().set_script<ButtonStartScript>();
			break;
		case ScriptSelect::PREVIEW:
		case ScriptSelect::SHOP:
			button_object.add_component<BehaviorScript>().set_script<ButtonScript>();
			break;
		case ScriptSelect::NONE:
			break;
	}
}
