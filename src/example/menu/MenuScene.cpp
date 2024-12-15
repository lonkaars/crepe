#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Asset.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Button.h>


#include "MenuScene.h"
#include "example/menu/MainMenuButton.h"

using namespace crepe;
using namespace std;

void MenuScene::load_scene() {

	GameObject camera = new_object("camera", "camera", vec2(0, 360));
	camera.add_component<Camera>(ivec2(1700, 720), vec2(2000, 800),
									Camera::Data{
										.bg_color = Color::RED,
									});

	GameObject menu_background = new_object("menu_background", "background", vec2(0, 0));

	MainMenuButton create_menu_buttons(*this);
}

string MenuScene::get_name() const { return "MenuScene"; }

GameObject MenuScene::create_object(const std::string & name, const std::string & tag,
							 const vec2 & position, double rotation, double scale) {
	return new_object(name, tag, position, rotation, scale);
}
