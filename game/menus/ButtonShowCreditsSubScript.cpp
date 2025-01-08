#include "ButtonShowCreditsSubScript.h"
#include "MenusConfig.h"
#include "mainmenu/CreditsSubScript.h"
#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void ButtonShowCreditsSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonShowCreditsSubScript::on_button_press(const ButtonPressEvent & e) {
	this->trigger_event<ShowCreditsEvent>();
	return false;
}
