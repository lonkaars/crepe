#include "ButtonSetMainMenuScript.h"
#include "MenusConfig.h"

using namespace crepe;
using namespace std;

void ButtonSetMainMenuScript::init(){
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool ButtonSetMainMenuScript::on_button_press(const ButtonPressEvent& e){
	this->set_next_scene(MAINMENU_SCENE);
	return false;
}

