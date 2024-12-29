#include "ButtonSetMainMenuScript.h"
#include "MainMenuConfig.h"
#include "iostream"

using namespace crepe;
using namespace std;

void ButtonSetMainMenuScript::init(){
	cout << "script init" << endl;
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool ButtonSetMainMenuScript::on_button_press(const ButtonPressEvent& e){
	this->set_next_scene(MainMenuConfig::MAINMENU_SCENE);
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}

