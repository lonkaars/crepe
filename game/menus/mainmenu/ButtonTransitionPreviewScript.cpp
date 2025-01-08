#include "ButtonTransitionPreviewScript.h"

#include "../MenusConfig.h"

using namespace crepe;
using namespace std;

void ButtonTransitionPreviewScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonTransitionPreviewScript::on_button_press(const ButtonPressEvent & e) {
	if (!this->transition) this->transition = true;
	return false;
}

const char * ButtonTransitionPreviewScript::get_scene_name() const {
	// Provide the next scene defined in MainMenuConfig
	return PREVIEW_SCENE;
}
