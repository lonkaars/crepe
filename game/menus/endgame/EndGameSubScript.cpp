#include "EndGameSubScript.h"

#include "../../Events.h"
#include "../ButtonReplaySubScript.h"
#include "../IFloatingWindowScript.h"
#include "../../Config.h"
#include "ValueBroker.h"
#include "manager/SaveManager.h"

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
	this->subscribe<ShowScoreEvent>([this](const ShowScoreEvent e) {
		return this->showscore();
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

bool EndGameSubScript::showscore(){
	// Gather text 
	Text & coins_text = this->get_components_by_name<Text>("gold_endgame").front().get();
	Text & distance_text = this->get_components_by_name<Text>("distance_endgame").front().get();
	Text & highscore_text = this->get_components_by_name<Text>("highscore_endgame").front().get();
	highscore_text.active = false;

	// Gather saved data
	SaveManager & savemgr = this->get_save_manager();
	ValueBroker<std::string> coins = savemgr.get<std::string>(TOTAL_COINS_RUN, "0");
	ValueBroker<std::string> distance = savemgr.get<std::string>(DISTANCE_RUN, "0");
	int distance_run = savemgr.get<int>(DISTANCE_RUN, 0).get();
	int distance_game = savemgr.get<int>(DISTANCE_GAME, 0).get();

	// Show highscore
	if(distance_run > distance_game) highscore_text.active = true;

	const float CHAR_SIZE_DIS = 20;
	// Show distance
	std::string distance_string = "DISTANCE:" + distance.get(); 
	distance_text.text = distance_string;
	crepe::vec2 size_distance = {CHAR_SIZE_DIS*distance_string.size(), (CHAR_SIZE_DIS*distance_string.size() / distance_string.size()) * 2};
	distance_text.dimensions = size_distance;

	const float CHAR_SIZE_COIN = 16;
	// Show coins
	std::string coins_string = "Coins:" + coins.get(); 
	coins_text.text = coins_string;
	crepe::vec2 size_coins = {CHAR_SIZE_COIN*coins_string.size(), (CHAR_SIZE_COIN*coins_string.size() / coins_string.size()) * 2};
	coins_text.dimensions = size_coins;

	return false;
}
