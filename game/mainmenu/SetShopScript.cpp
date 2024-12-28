#include "SetShopScript.h"
#include "MainMenuConfig.h"
#include "iostream"

using namespace crepe;
using namespace std;

void SetShopScript::init(){
	cout << "script init" << endl;
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool SetShopScript::on_button_press(const ButtonPressEvent& e){
	this->set_next_scene(MainMenuConfig::SHOP_SCENE);
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}

