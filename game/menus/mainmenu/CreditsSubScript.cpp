#include "CreditsSubScript.h"

#include "../../Events.h"
#include "../IFloatingWindowScript.h"
#include "../ButtonReplaySubScript.h"

#include <string>

#include <crepe/api/Button.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>
#include <crepe/types.h>

using namespace crepe;

CreditsSubScript::CreditsSubScript(const std::string & tag) { this->tag = tag; }

void CreditsSubScript::init() {
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
