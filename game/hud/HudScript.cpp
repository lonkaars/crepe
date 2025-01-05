#include "HudScript.h"
#include "api/Text.h"
#include "api/Transform.h"
#include "manager/SaveManager.h"
#include "../Config.h"
#include "HudConfig.h"

using namespace crepe;
using namespace std;

void HudScript::init() {
	savemgr = &this->get_save_manager();
	savemgr->set(TOTAL_COINS_RUN,0);
	Text & txt = this->get_components_by_name<Text>(HUD_BEST).front();
	string record = BEST+to_string(savemgr->get<int>(DISTANCE_GAME,0).get())+DISTANCE_UNIT;
	txt.text = record;
}

void HudScript::frame_update(crepe::duration_t dt) {
	
	// string number = std::to_string(savemgr->get<int>(DISTANCE_RUN,0).get());

	// Distance
	Text & txt_dt = this->get_components_by_name<Text>(HUD_DISTANCE).front();
	Transform & tf = this->get_components_by_name<Transform>(PLAYER_NAME).front();
	string distance = to_string(static_cast<int>(tf.position.x/STEP_SIZE_DISTANCE)) + DISTANCE_UNIT;
	txt_dt.text = distance;

	// Coins
	Text & txt_co = this->get_components_by_name<Text>(HUD_COINS).front();
	string amount_of_coins = to_string(savemgr->get<int>(TOTAL_COINS_RUN,0).get());
	txt_co.text = amount_of_coins;
}
