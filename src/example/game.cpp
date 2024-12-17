#include "Background.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/types.h>
#include <iostream>

using namespace crepe;
using namespace std;

class MoveCameraScript : public Script {
public:
	void init() {
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
	}

private:
	bool keypressed(const KeyPressEvent & event) {
		if (event.key == Keycode::RIGHT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x += 100;
		} else if (event.key == Keycode::LEFT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x -= 100;
		}
		return true;
	}
};

class Scene1 : public Scene {
public:
	void load_scene() {
		Background background(*this);

		GameObject camera = new_object("camera", "camera", vec2(600, 0));
		camera.add_component<Camera>(ivec2(1700, 720), vec2(2000, 800),
									 Camera::Data{
										 .bg_color = Color::RED,
									 });
		camera.add_component<BehaviorScript>().set_script<MoveCameraScript>();
		camera.add_component<Rigidbody>(Rigidbody::Data{
			.linear_velocity = vec2(100, 0),
		});
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	LoopManager gameloop;
	gameloop.add_scene<Scene1>();
	gameloop.start();
	return 0;
}
