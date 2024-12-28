#include "ShowPreviewScript.h"
#include "MainMenuConfig.h"
#include "iostream"

using namespace crepe;
using namespace std;


void ShowPreviewScript::init(){
	cout << "script init" << endl;
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool ShowPreviewScript::on_button_press(const ButtonPressEvent& e){
	if(!this->transition)	this->transition = true;
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}

const char* ShowPreviewScript::get_scene_name() const {
    // Provide the next scene defined in MainMenuConfig
    return MainMenuConfig::PREVIEW_SCENE;
}
