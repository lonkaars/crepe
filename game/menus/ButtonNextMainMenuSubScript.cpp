#include "ButtonNextMainMenuSubScript.h"
#include "ButtonReplaySubScript.h"
#include "MenusConfig.h"
#include "ValueBroker.h"

#include "manager/SaveManager.h"

#include "../Config.h"

#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void ButtonNextMainMenuSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonNextMainMenuSubScript::on_button_press(const ButtonPressEvent & e) {
	RefVector<AudioSource> audios
		= this->get_components_by_name<AudioSource>("background_music");

	for (AudioSource & audio : audios) {
		audio.stop();
	}

	this->trigger_event<DeleteRecordingEvent>();
	SaveManager & savemgr = this->get_save_manager();

	ValueBroker<int> coins = savemgr.get<int>(TOTAL_COINS_RUN, 0);
	ValueBroker<int> coins_game = savemgr.get<int>(TOTAL_COINS_GAME, 0);
	savemgr.set(TOTAL_COINS_GAME, coins_game.get() + coins.get());

	ValueBroker<int> distance = savemgr.get<int>(DISTANCE_RUN, 0);
	ValueBroker<int> distance_game = savemgr.get<int>(DISTANCE_GAME, 0);
	if (distance.get() > distance_game.get()) savemgr.set(DISTANCE_GAME, distance.get());

	this->set_next_scene(MAINMENU_SCENE);
	return false;
}
