#include "GameScene.h"
#include "Background.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/types.h>

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

void GameScene::load_scene() {
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

string GameScene::get_name() const { return "scene1"; }
