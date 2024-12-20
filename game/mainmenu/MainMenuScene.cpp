
#include "MainMenuScene.h"
#include "ButtonSubScene.h"
#include "api/Camera.h"

using namespace crepe;
using namespace std;

void MainMenuScene::load_scene(){
	GameObject camera_object = this->new_object("camera");
	camera_object.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
	Camera::Data{
		.bg_color = Color::RED,
	});
	
	ButtonSubScene button;
	button.create(*this);
}

string MainMenuScene::get_name() const { return "mainmenu"; }
