#include "CreditsSubScript.h"

#include "../../Events.h"
#include "../ButtonReplaySubScript.h"
#include "../IFloatingWindowScript.h"

#include <string>

#include <crepe/api/Button.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>
#include <crepe/types.h>

using namespace crepe;

CreditsSubScript::CreditsSubScript(const std::string & tag) { this->tag = tag; }

void CreditsSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
	this->subscribe<ShowCreditsEvent>([this](const ShowCreditsEvent & e) {
		this->enable_all();
		return false;
	});
	this->disable_all();
}

bool CreditsSubScript::disable_all() {
	IFloatingWindowScript::disable_all_sprites();
	RefVector<Button> buttons = this->get_components_by_tag<Button>(this->tag);
	for (Button & button : buttons) {
		button.active = false;
	}
	RefVector<Text> texts = this->get_components_by_tag<Text>(this->tag);
	for (Text & text : texts) {
		text.active = false;
	}
	return false;
}

bool CreditsSubScript::enable_all() {
	IFloatingWindowScript::enable_all_sprites();
	RefVector<Button> buttons = this->get_components_by_tag<Button>(this->tag);
	for (Button & button : buttons) {
		button.active = true;
	}
	RefVector<Text> texts = this->get_components_by_tag<Text>(this->tag);
	for (Text & text : texts) {
		text.active = true;
	}
	return false;
}

bool CreditsSubScript::on_button_press(const ButtonPressEvent & e) {
	return this->disable_all();
}
