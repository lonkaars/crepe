#include "HudSubScene.h"
#include "api/GameObject.h"
#include "api/Text.h"
#include "../Config.h"
#include "HudConfig.h"

using namespace crepe;
using namespace std;

void HudSubScene::create(Scene & scn){
	
	// Distance
	GameObject hud_dis = scn.new_object(HUD_DISTANCE);
	crepe::vec2 size_distance = {DISTANCE_WIDTH,(DISTANCE_WIDTH/DISTANCE_LENGTH)*2};
	hud_dis.add_component<Text>(size_distance, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::WHITE,
	}, TOP_LEFT+FONTOFFSET, DISTANCE_PLACEHOLDER);

	// Best
	GameObject hud_best = scn.new_object(HUD_BEST);
	crepe::vec2 size_best = {BEST_WIDTH,(BEST_WIDTH/BEST_LENGTH)*2};
	hud_best.add_component<Text>(size_best, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::WHITE,
	}, TOP_LEFT+FONTOFFSET+BEST_OFFSET, BEST);

	// Coins
	GameObject hud_coin = scn.new_object(HUD_COINS);
	crepe::vec2 size = {COINS_WIDTH,(COINS_WIDTH/COINS_LENGTH)*2};
	hud_coin.add_component<Text>(size, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::WHITE,
	}, TOP_LEFT+FONTOFFSET+COINS_OFFSET, COINS);
}
