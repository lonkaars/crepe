#include "MainMenuButton.h"
#include "api/Color.h"
#include "api/Script.h"
#include "example/menu/MainMenuScript.h"
#include "types.h"
#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Asset.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Button.h>
#include <iostream>


using namespace crepe;
using namespace std;

MainMenuButton::MainMenuButton(MenuScene& from_scene) : scene(from_scene) {
	this->place_btn();
}


void MainMenuButton::place_btn(){
	// Determine start of table
	const ivec2 start_position = {BTN_OFFSET_COLUM, BTN_START_ROW};
	// Determine size of row (Height)
	const int row_size = (BTN_END_ROW - BTN_START_ROW) / BTN_AMOUNT - BTN_SPACING_ROW;
	// Initialize button placement (each button in the row)
	float amount = 0;
	MainMenuScript test;
	GameObject menu = this->scene.create_object("menu", "menu");
	BehaviorScript & script = menu.add_component<BehaviorScript>().set_script<MainMenuScript>();



	// Start position of first button
	vec2 button_position = {static_cast<float>(start_position.x + BTN_WITDH_COLUM / 2), start_position.y + (row_size * amount++)};
	this->place_btn_preview(menu,button_position, vec2{BTN_WITDH_COLUM, row_size - BTN_SPACING_ROW});
	button_position.y += (row_size * amount++);
	this->place_btn_jetpack(menu,button_position, vec2{BTN_WITDH_COLUM, row_size - BTN_SPACING_ROW});
}

void MainMenuButton::place_btn_preview(GameObject & menu,const vec2 &position,const vec2& size){
	Asset button_start_img{"asset/texture/test_ap43.png"};

	Sprite &sprite = menu.add_component<Sprite>(button_start_img,Sprite::Data{
		.sorting_in_layer = STARTING_LAYER,
		.order_in_layer = STARTING_LAYER,
		.size = size,
		.position_offset = position,
	});

	//create button and link functions
	Button& button_temp = menu.add_component<Button>(size, position,[&]() { this->click_btn_preview(); },false);
	// on_mouse_enter
	button_temp.on_mouse_enter = [&]() { this->enter_button(&sprite); };  
	// on_mouse_exit
	button_temp.on_mouse_exit = [&]() { this->exit_button(&sprite); };    

}

void MainMenuButton::place_btn_jetpack(GameObject & menu,const vec2 &position,const vec2& size){
	Asset button_start_img{"asset/texture/test_ap43.png"};
		
	Sprite &sprite = menu.add_component<Sprite>(button_start_img,Sprite::Data{
		.sorting_in_layer = STARTING_LAYER,
		.order_in_layer = STARTING_LAYER,
		.size = size,
		.position_offset = position,
	});

	//create button and link functions
	Button& button_temp = menu.add_component<Button>(size, position,[&]() { this->click_btn_jetpack(); },false);
	// on_mouse_enter
	button_temp.on_mouse_enter = [&]() { this->enter_button(&sprite); };  
	// on_mouse_exit
	button_temp.on_mouse_exit = [&]() { this->exit_button(&sprite); };    

}

void MainMenuButton::click_btn_preview(){
	std::cout << "button clicked preview" << std::endl;
}

void MainMenuButton::click_btn_jetpack(){
	std::cout << "button clicked jetpack" << std::endl;
}


void MainMenuButton::enter_button(Sprite* button_sprite){
	std::cout << "enter" << std::endl;
	Color color(150,150,150,0xff);
	button_sprite->data.color = color;
}

void MainMenuButton::exit_button(Sprite* button_sprite){
	std::cout << "exit" << std::endl;
	Color color(0xff,0xff,0xff,0xff);
	button_sprite->data.color = color;
}

