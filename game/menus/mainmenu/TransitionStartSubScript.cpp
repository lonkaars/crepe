#include "TransitionStartSubScript.h"

#include "../MenusConfig.h"

using namespace crepe;
using namespace std;

void TransitionStartSubScript::fixed_update(crepe::duration_t dt) {
	if (this->get_key_state(Keycode::ENTER) && this->transition == false)
		this->transition = true;
}

const char * TransitionStartSubScript::get_scene_name() const {
	// Provide the next scene defined in MainMenuConfig
	return START_SCENE;
}
