#include "ShowPreviewScript.h"
#include "MainMenuConfig.h"
#include "iostream"

using namespace crepe;
using namespace std;


void ShowPreviewScript::init(){
	cout << "script init" << endl;
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
}

bool ShowPreviewScript::on_button_press(const ButtonPressEvent& e){
	if(!this->transition)	this->transition = true;
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ShowPreviewScript::on_button_enter(const ButtonEnterEvent& e){

	cout << "Start Enter:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ShowPreviewScript::on_button_exit(const ButtonExitEvent& e){

	cout << "Start Exit:" << e.metadata.game_object_id << std::endl;
	return false;
}

const char* ShowPreviewScript::get_scene_name() const {
    // Provide the next scene defined in MainMenuConfig
    return MainMenuConfig::PREVIEW_SCENE;
}
