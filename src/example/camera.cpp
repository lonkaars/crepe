

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Point.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/event.h>
#include <crepe/api/eventHandler.h>
#include <crepe/api/eventManager.h>
#include <crepe/api/loopManager.h>
#include <crepe/keyCodes.h>
#include <cstdint>
#include <iostream>
#include <memory>

using namespace crepe;

int cam_x = 0;
int cam_y = 0;
double zoom = 1;

void on_key_pressed(const KeyPressedEvent & e) {

	switch (e.getKeyCode()) {
		case A:
			cam_x += 20;
			break;
		case W:
			cam_y += 20;
			break;
		case D:
			cam_x -= 20;
			break;
		case S:
			cam_y -= 20;
			break;
		case Z:
			zoom -= 0.01;
			break;
		case X:
			zoom += 0.01;
			break;
		default:
			break;
	}
}

class MyCameraScript : public Script {
	void update() {
		/*
		auto & cam = this->get_component<Camera>();
		cam.x = cam_x;
		cam.y = cam_y;
		cam.zoom = zoom;
		*/
	}
};

//FIXME:
// auto var = GameObject(); --> will give an exception 
// eventtouh i only created it once

int main() {
	LoopManager mgr;

	subscribe<KeyPressedEvent>(on_key_pressed);

	GameObject bg(0, "background", "TAG", Point{0, 0}, 0, 1);
	GameObject camera(1, "MainCamera", "TAG", Point{0, 0}, 0, 1);

	{
		Color color(0, 0, 0, 0);
		bg.add_component<Sprite>(
			std::make_shared<Texture>("../asset/texture/world.png"), color,
			FlipSettings{false, false});
	}
	{
		camera.add_component<Camera>(Color::get_white());
		//camera.add_component<BehaviorScript>().set_script<MyCameraScript>();
	}

	mgr.setRunning(true);
	mgr.setup();
	mgr.loop();
}
