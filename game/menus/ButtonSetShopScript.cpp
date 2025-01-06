#include "ButtonSetShopScript.h"
#include "iostream"
#include "MenusConfig.h"

using namespace crepe;
using namespace std;

void ButtonSetShopScript::init(){
	cout << "script init" << endl;
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
}

bool ButtonSetShopScript::on_button_press(const ButtonPressEvent& e){
	this->set_next_scene(SHOP_SCENE);
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}

