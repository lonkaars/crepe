#include "ButtonSubScene.h"
#include "ButtonScript.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Button.h>

using namespace crepe;
using namespace std;

void ButtonSubScene::create(Scene & scn){
	GameObject button_object = scn.new_object("button");
	button_object.add_component<Button>(vec2{100,100},vec2{0,0});
	button_object.add_component<Sprite>(Asset("asset/coin/coin_64.png"),Sprite::Data{
	.size = vec2{100,100},
	});
	button_object.add_component<BehaviorScript>().set_script<ButtonScript>();
}

