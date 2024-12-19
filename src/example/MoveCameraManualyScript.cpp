#include "MoveCameraManualyScript.h"

using namespace crepe;
using namespace std;

void MoveCameraManualyScript::init() {
	subscribe<KeyPressEvent>(
		[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
}

bool MoveCameraManualyScript::keypressed(const KeyPressEvent & event) {
	if (event.key == Keycode::RIGHT) {
		Transform & cam = this->get_components_by_name<Transform>("camera").front();
		cam.position.x += 100;
		return true;
	} else if (event.key == Keycode::LEFT) {
		Transform & cam = this->get_components_by_name<Transform>("camera").front();
		cam.position.x -= 100;
		return true;
	}
	return false;
}
