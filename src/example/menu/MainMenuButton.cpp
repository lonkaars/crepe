#include "MainMenuButton.h"
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

MainMenuButton::MainMenuButton(Scene0& from_scene) : scene(from_scene) {
	this->place_btn();
}


void MainMenuButton::place_btn(){
	constexpr ivec2 START_POS = {BTN_OFFSET_COLUM,BTN_START_ROW};
	constexpr int ROW_SIZE = (BTN_END_ROW-BTN_START_ROW)/BTN_AMOUNT-BTN_SPACING_ROW;

	float amount = 0;
	place_btn_preview(vec2{START_POS.x+BTN_WITDH_COLUM/2,START_POS.y+(ROW_SIZE*amount++)},vec2{BTN_WITDH_COLUM,ROW_SIZE-BTN_SPACING_ROW});
	place_btn_preview(vec2{START_POS.x+BTN_WITDH_COLUM/2,START_POS.y+(ROW_SIZE*amount++)},vec2{BTN_WITDH_COLUM,ROW_SIZE-BTN_SPACING_ROW});

}

void MainMenuButton::place_btn_preview(const vec2 &position,const vec2& size){
	GameObject button_start = this->scene.create_object("button_start", "start");
	Asset button_start_img{"asset/texture/test_ap43.png"};
	button_start.add_component<Sprite>(button_start_img,Sprite::Data{
		.sorting_in_layer = STARTING_LAYER,
		.order_in_layer = STARTING_LAYER,
		.size = size,
		.position_offset = position,
	});

	std::function<void()> on_click = [&]() { std::cout << "button clicked" << std::endl; };
	std::function<void()> on_enter = [&]() { std::cout << "enter" << std::endl; };
	std::function<void()> on_exit = [&]() { std::cout << "exit" << std::endl; };
	Button & button_temp = button_start.add_component<Button>(size, position, on_click, false);
	button_temp.on_click = on_click;
	button_temp.on_mouse_enter = on_enter;
	button_temp.on_mouse_exit = on_exit;
}
