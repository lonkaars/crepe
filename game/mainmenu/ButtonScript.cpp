#include "ButtonScript.h"
#include "iostream"
using namespace crepe;
using namespace std;

bool ButtonScript::on_button_press(const ButtonPressEvent& e){

	cout << "button triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ButtonScript::on_button_enter(const ButtonEnterEvent& e){

	cout << "button Enter:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ButtonScript::on_button_exit(const ButtonExitEvent& e){

	cout << "button Exit:" << e.metadata.game_object_id << std::endl;
	return false;
}
void ButtonScript::init(){
	cout << "script init" << endl;
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
}
