#include "IButtonScript.h"
#include "api/Sprite.h"
#include "iostream"
#include "system/InputSystem.h"
#include "types.h"
using namespace crepe;
using namespace std;

void IButtonScript::init(){
	cout << "script init" << endl;
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
}
bool IButtonScript::on_button_exit(const ButtonExitEvent& e){
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for(Sprite & sprite : sprites)
	{
		sprite.data.color = Color{255,255,255,255};
	}

	cout << "button triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool IButtonScript::on_button_enter(const ButtonEnterEvent& e){
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for(Sprite & sprite : sprites)
	{
		sprite.data.color = Color{200,200,200,255};
	}
	cout << "button Enter:" << e.metadata.game_object_id << std::endl;
	return false;
}

