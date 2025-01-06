#include "TransitionStartScript.h"

#include "../MenusConfig.h"

using namespace crepe;
using namespace std;

void TransitionStartScript::fixed_update(crepe::duration_t dt){
	if(this->get_key_state(Keycode::ENTER) && this->transition == false) this->transition = true;
}

const char* TransitionStartScript::get_scene_name() const {
    // Provide the next scene defined in MainMenuConfig
    return START_SCENE;
}
