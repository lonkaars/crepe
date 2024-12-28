#include "IButtonScript.h"
#include "iostream"
#include "system/InputSystem.h"
using namespace crepe;
using namespace std;

void IButtonScript::init(){
	cout << "script init" << endl;
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
}
bool IButtonScript::on_button_exit(const ButtonExitEvent& e){

	cout << "button triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool IButtonScript::on_button_enter(const ButtonEnterEvent& e){

	cout << "button Enter:" << e.metadata.game_object_id << std::endl;
	return false;
}

