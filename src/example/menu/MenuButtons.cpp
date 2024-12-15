#include "MenuButtons.h"
#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Asset.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Button.h>


MainMenuButton::MainMenuButton(crepe::Scene& from_scene) : scene(from_scene) {}

void MainMenuButton::calculate_btn_pos(){

}
void MainMenuButton::place_btn(){


}

void MainMenuButton::place_btn_preview(){
	GameObject button_start = this->scene.new_object("button_start", "start", vec2{0, 0}, 0, 1);
	Asset button_start_img{"asset/texture/test_ap43.png"};
	button_start.add_component<Sprite>(button_start_img,Sprite::Data{
		.sorting_in_layer = 1,
		.order_in_layer = 1,
		.size = {200,200}
		
	});

	std::function<void()> on_click = [&]() { std::cout << "button clicked" << std::endl; };
	std::function<void()> on_enter = [&]() { std::cout << "enter" << std::endl; };
	std::function<void()> on_exit = [&]() { std::cout << "exit" << std::endl; };
	Button & button_temp = button_start.add_component<Button>(vec2{100, 100}, vec2{0, 0}, on_click, false);
	button_temp.on_click = on_click;
	button_temp.on_mouse_enter = on_enter;
	button_temp.on_mouse_exit = on_exit;
}
