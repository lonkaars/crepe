#include "ButtonSetMainMenuScript.h"
#include "MenusConfig.h"
#include "api/AudioSource.h"
#include "types.h"

using namespace crepe;
using namespace std;

void ButtonSetMainMenuScript::init(){
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool ButtonSetMainMenuScript::on_button_press(const ButtonPressEvent& e){
	RefVector<AudioSource> audios = this->get_components_by_name<AudioSource>("background_music");
	
	for (AudioSource & audio : audios) {
		audio.stop();
	}

	this->set_next_scene(MAINMENU_SCENE);
	return false;
}

