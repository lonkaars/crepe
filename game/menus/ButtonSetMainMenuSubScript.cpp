#include "ButtonSetMainMenuSubScript.h"
#include "MenusConfig.h"

#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void ButtonSetMainMenuSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonSetMainMenuSubScript::on_button_press(const ButtonPressEvent & e) {
	RefVector<AudioSource> audios
		= this->get_components_by_name<AudioSource>("background_music");

	this->set_next_scene(MAINMENU_SCENE);
	return false;
}
