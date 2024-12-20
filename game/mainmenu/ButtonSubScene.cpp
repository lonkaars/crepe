#include "ButtonSubScene.h"
#include "ButtonScript.h"

#include "system/RenderSystem.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Button.h>
#include <crepe/api/Text.h>

using namespace crepe;
using namespace std;

void ButtonSubScene::create(Scene & scn){
	GameObject button_object = scn.new_object("button");
	button_object.add_component<Button>(vec2{250,100},vec2{0,0});
	button_object.add_component<BehaviorScript>().set_script<ButtonScript>();
	this->large_btn_overlay(button_object);
}
void ButtonSubScene::large_btn_overlay(crepe::GameObject & button_object){
	button_object.add_component<Sprite>(Asset("asset/ui/buttonBacking.png"),Sprite::Data{
		.sorting_in_layer = 0,
		.size = vec2{250,100},
	});
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.sorting_in_layer = 1,
		.size = vec2{50,150},
		.position_offset = {110,0},
	});
	button_object.add_component<Sprite>(Asset("asset/ui/buttonSmallBlue.png"),Sprite::Data{
		.flip = {true,false},
		.sorting_in_layer = 1,
		.size = vec2{75,150},
		.position_offset = {-110,0},
	});
	//fc-match arial
	button_object.add_component<Text>(vec2{220,100},vec2{0,0}, "dejavusans", Text::Data{
		.text_color = Color::MAGENTA,
		}, "Hallo");

}
