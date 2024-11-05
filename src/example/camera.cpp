


#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Point.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/keyCodes.h>
#include <crepe/api/Script.h>
#include <crepe/api/event.h>
#include <crepe/api/loopManager.h>
#include <crepe/api/eventManager.h>
#include <crepe/api/eventHandler.h>
#include <cstdint>
#include <iostream>
#include <memory>

using namespace crepe;


class CameraTest : public Event {

public:
	CameraTest() : Event("MoveCamera"){};

	REGISTER_EVENT_TYPE(CameraTest);
};


uint8_t cam_x = 0;
uint8_t cam_y = 0;

void camera_movement(const CameraTest& cam){

}

void on_key_pressed(const KeyPressedEvent& e){
	
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
		default:
			break;

	}
	std::cout << e.getKeyCode() << std::endl;
}

class MyCameraScript : public Script {
	void update(){
		auto& cam = this->get_component<Camera>();
		cam.x = cam_x;
		cam.y = cam_y;
	}

};

int main() {
	LoopManager mgr;

	subscribe<KeyPressedEvent>(on_key_pressed);
	subscribe<CameraTest>(camera_movement);

	
	auto bg = GameObject(0, "background", "TAG", 0);
	auto camera = GameObject(0, "MainCamera", "TAG", 0);

	{
		Color color(0,0,0,0);
		Point point = { .x = 0, .y = 0, };
		bg.add_component<Transform>(point, 0, 1);
		bg.add_component<Sprite>(std::make_shared<Texture>("../asset/texture/world.png"), color, FlipSettings{false,false});
	}
	{
		camera.add_component<Camera>(Color::get_white());
		camera.add_component<BehaviorScript>().set_script<MyCameraScript>();
	}


	mgr.setRunning(true);
	mgr.setup();
	mgr.loop();


}
