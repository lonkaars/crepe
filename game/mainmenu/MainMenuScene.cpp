
#include "MainMenuScene.h"
#include "ButtonSubScene.h"
#include "api/Camera.h"

using namespace crepe;
using namespace std;

void MainMenuScene::load_scene(){
	GameObject camera_object = this->new_object("camera");
	camera_object.add_component<Camera>(ivec2{500,500},vec2{500,500},Camera::Data{});
	
	ButtonSubScene button;
	button.create(*this);
}

string MainMenuScene::get_name() const { return "mainmenu"; }
