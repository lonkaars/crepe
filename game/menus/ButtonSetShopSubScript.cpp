#include "ButtonSetShopSubScript.h"
#include "MenusConfig.h"

using namespace crepe;
using namespace std;

void ButtonSetShopSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonSetShopSubScript::on_button_press(const ButtonPressEvent & e) {
	this->set_next_scene(SHOP_SCENE);
	return false;
}
