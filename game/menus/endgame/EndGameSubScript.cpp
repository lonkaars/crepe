#include "EndGameSubScript.h"

#include "../../Events.h"
#include "../IFloatingWindowScript.h"

#include <string>

#include <crepe/api/Button.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>
#include <crepe/types.h>

using namespace crepe;

EndGameSubScript::EndGameSubScript(const std::string & tag) { this->tag = tag; }

void EndGameSubScript::init() {
	this->disable_all();
	this->subscribe<EndGameEvent>([this](const EndGameEvent e) { return this->enable_all(); });
	this->subscribe<EndGameEvent>([this](const EndGameEvent e) {
		return this->reset_timescale();
	});
}

bool EndGameSubScript::disable_all() {
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

bool EndGameSubScript::enable_all() {
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

bool EndGameSubScript::reset_timescale() {
	this->get_loop_timer().set_time_scale(1);
	return false;
}
