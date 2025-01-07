#include "IButtonScript.h"

#include "system/InputSystem.h"

#include <crepe/types.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

void IButtonScript::init(){
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
}
bool IButtonScript::on_button_exit(const ButtonExitEvent& e){
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for(Sprite & sprite : sprites)
	{
		sprite.data.color = Color{255,255,255,255};
	}
	return false;
}
bool IButtonScript::on_button_enter(const ButtonEnterEvent& e){
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for(Sprite & sprite : sprites)
	{
		sprite.data.color = Color{200,200,200,255};
	}
	return false;
}

