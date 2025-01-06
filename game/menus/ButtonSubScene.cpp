#include "ButtonSubScene.h"
#include "ButtonSetMainMenuScript.h"
#include "ButtonSetShopScript.h"
#include "IButtonScript.h"
#include "MenusConfig.h"

#include "mainmenu/ButtonTransitionPreviewScript.h"

#include "../Config.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Button.h>
#include <crepe/api/Text.h>
#include <crepe/api/Color.h>

using namespace crepe;
using namespace std;

void ButtonSubScene::create(Scene & scn,const Data & data){
	GameObject button_object = scn.new_object("button",data.tag,data.position,0,data.scale);
	this->set_button_overlay(button_object,data);
	this->btn_text(button_object,data);
	this->set_script(button_object,data);
	this->set_icon(button_object,data);
}

void ButtonSubScene::btn_text(crepe::GameObject & button_object,const Data & data){

	crepe::vec2 size = {data.text_width,(data.text_width/data.text.size())*2};
	button_object.add_component<Text>(size, FONT,Text::Data{
		.world_space = data.worldspace,
		.text_color = Color::WHITE,
	}, data.text_offset+FONTOFFSET, data.text);
}

void ButtonSubScene::set_script(crepe::GameObject & button_object,const Data & data){
	switch (data.script_type) {
		case ScriptSelect::PREVIEW:
			button_object.add_component<BehaviorScript>().set_script<ButtonTransitionPreviewScript>();
			break;
		case ScriptSelect::SHOP:
			button_object.add_component<BehaviorScript>().set_script<ButtonSetShopScript>();
			break;
		case ScriptSelect::MAINMENU:
			button_object.add_component<BehaviorScript>().set_script<ButtonSetMainMenuScript>();
			break;
		case ScriptSelect::NONE:
			button_object.add_component<BehaviorScript>().set_script<IButtonScript>();
			break;
	}
}

void ButtonSubScene::set_icon(crepe::GameObject & button_object,const Data & data){
	switch (data.icon_type) {
		case IconSelect::SHOP:
			button_object.add_component<Sprite>(Asset("asset/ui/buttonCoinsSmall.png"),Sprite::Data{
				.sorting_in_layer = STARTING_SORTING_IN_LAYER+3,
				.size = ICON_SIZE,
				.position_offset = data.icon_offset,
				.world_space = data.worldspace,
			});
			break;
		case IconSelect::COINS:
			button_object.add_component<Sprite>(Asset("asset/ui/buttonCoinsSmall.png"),Sprite::Data{
				.sorting_in_layer = STARTING_SORTING_IN_LAYER+3,
				.size = ICON_SIZE,
				.position_offset = data.icon_offset,
				.world_space = data.worldspace,
			});
			break;
		case IconSelect::NONE:
			break;
	}
}

void ButtonSubScene::set_button_overlay(crepe::GameObject & button_object,const Data & data){
	switch (data.button_type) {
		case ButtonSelect::LARGE:
			this->large_btn_overlay(button_object,data);
			break;
		case ButtonSelect::BACK:
			this->small_btn_overlay(button_object,data);
			break;
		case ButtonSelect::NEXT:
			this->small_btn_overlay(button_object,data);
			break;
	}
}

void ButtonSubScene::large_btn_overlay(crepe::GameObject & button_object,const Data & data){
	button_object.add_component<Sprite>(Asset("asset/ui/buttonBacking.png"),Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+1,
		.size = LARGE_OVERLAY_SIZE,
		.world_space = data.worldspace,
	});
	button_object.add_component<Button>(LARGE_OVERLAY_SIZE,Button::Data{});
	if(!data.color_side) return;
	this->btn_color_side(button_object,SIDE_PANEL_OFFSET,data);
}

void ButtonSubScene::small_btn_overlay(crepe::GameObject & button_object,const Data & data){
	button_object.add_component<Sprite>(Asset("asset/ui/backbuttonright.png"),Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+1,
		.size = SMALL_OVERLAY_SIZE_RIGHT,
		.position_offset = {20,0},
		.world_space = data.worldspace,
	});
	button_object.add_component<Sprite>(Asset("asset/ui/backbuttonleft.png"),Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+1,
		.size = SMALL_OVERLAY_SIZE_LEFT,
		.position_offset = {-80,0},
		.world_space = data.worldspace,
	});
	button_object.add_component<Button>(vec2{SMALL_OVERLAY_SIZE_LEFT.x+SMALL_OVERLAY_SIZE_RIGHT.x,SMALL_OVERLAY_SIZE_LEFT.y},Button::Data{});
}

void ButtonSubScene::btn_color_side(crepe::GameObject & button_object,const vec2 & offset,const Data & data){
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+2,
		.size = SIDE_PANEL_SIZE,
		.position_offset = offset,
		.world_space = data.worldspace,
	});
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.flip = {true,false},
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+2,
		.size = SIDE_PANEL_SIZE,
		.position_offset = {-offset.x,offset.y},
		.world_space = data.worldspace,
	});
}
