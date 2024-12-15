#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Asset.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Button.h>
#include <iostream>

#include "Menu.h"

using namespace crepe;
using namespace std;

void Scene0::load_scene() {
	Mediator & m = this->mediator;
	ComponentManager & mgr = m.component_manager;

	GameObject camera = mgr.new_object("camera", "camera", vec2(0, 360));
	camera.add_component<Camera>(ivec2(1700, 720), vec2(2000, 800),
									Camera::Data{
										.bg_color = Color::RED,
									});

	GameObject menu_background = mgr.new_object("menu_background", "background", vec2(0, 0));

}

string Scene0::get_name() const { return "scene0"; }

