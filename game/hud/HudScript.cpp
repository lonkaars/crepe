#include "HudScript.h"
#include "api/Text.h"
#include "api/Transform.h"
#include "manager/SaveManager.h"
#include "../Config.h"
#include "HudConfig.h"
#include <climits>

using namespace crepe;
using namespace std;

void HudScript::init() {
	savemgr = &this->get_save_manager();
	savemgr->set(TOTAL_COINS_RUN,0);
	Text & txt = this->get_components_by_name<Text>(HUD_BEST).front();
	string record = BEST+to_string(savemgr->get<int>(DISTANCE_GAME,0).get())+DISTANCE_UNIT;
	txt.text = record;
	txt.dimensions = {BEST_CHAR_WIDTH*record.size(),(BEST_CHAR_WIDTH)*2};
	txt.offset = TOP_LEFT+FONTOFFSET+BEST_OFFSET + vec2{record.size() * BEST_CHAR_WIDTH/2,0};
	
	this->subscribe<GetCoinEvent>([this](const GetCoinEvent e)-> bool { return this->get_coin(e); });
	this->subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		if(ev.key != Keycode::END) return false;
		Text & txt_fps = this->get_components_by_name<Text>(HUD_FPS).front();
		this->show_fps = !this->show_fps;
		if(this->show_fps)
		{
			txt_fps.active = true;
		}
		else {
			txt_fps.active = false;
		}
		return true;
	});
}

void HudScript::frame_update(crepe::duration_t dt) {
	
	// Distance
	Text & txt_dt = this->get_components_by_name<Text>(HUD_DISTANCE).front();
	Transform & tf = this->get_components_by_name<Transform>(PLAYER_NAME).front();
	string distance = to_string(static_cast<int>(tf.position.x/STEP_SIZE_DISTANCE)) + DISTANCE_UNIT;
	txt_dt.text = distance;
	txt_dt.dimensions = {DISTANCE_CHAR_WIDTH*distance.size(),(DISTANCE_CHAR_WIDTH)*2};
	txt_dt.offset = TOP_LEFT+FONTOFFSET + vec2{distance.size() * DISTANCE_CHAR_WIDTH/2,0};

	// Coins
	Text & txt_co = this->get_components_by_name<Text>(HUD_COINS).front();
	string amount_of_coins = to_string(this->coin_amount);
	txt_co.text = amount_of_coins;
	txt_co.dimensions = {COINS_CHAR_WIDTH*amount_of_coins.size(),(COINS_CHAR_WIDTH)*2};
	txt_co.offset = TOP_LEFT+FONTOFFSET+COINS_OFFSET + vec2{amount_of_coins.size() * COINS_CHAR_WIDTH/2,0};

	// FPS
	Text & txt_fps = this->get_components_by_name<Text>(HUD_FPS).front();
	float fps = this->get_loop_timer().get_fps();
	string fps_amount = to_string(this->get_loop_timer().get_fps());
	txt_fps.text = fps_amount;
	txt_fps.dimensions = {FPS_CHAR_WIDTH*fps_amount.size(),(FPS_CHAR_WIDTH)*2};
	txt_fps.offset = TOP_LEFT+FONTOFFSET+FPS_OFFSET + vec2{fps_amount.size() * FPS_CHAR_WIDTH/2,0};
	if(fps >= 30) txt_fps.data.text_color = Color::YELLOW;
	if(fps >= 50) txt_fps.data.text_color = Color::GREEN;
	if(fps < 30) txt_fps.data.text_color = Color::RED;
}


bool HudScript::get_coin(const GetCoinEvent e){
	this->coin_amount = e.amount_of_coins;
	return true;
}

