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

	crepe::vec2 size_distance = {DISTANCE_CHAR_WIDTH*DISTANCE_LENGTH,(DISTANCE_CHAR_WIDTH)*2};
	hud_dis.add_component<Text>(size_distance, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::WHITE,
	}, TOP_LEFT+FONTOFFSET + vec2{DISTANCE_LENGTH * DISTANCE_CHAR_WIDTH/2,0}, DISTANCE_PLACEHOLDER);

	// Best
	GameObject hud_best = scn.new_object(HUD_BEST);
	crepe::vec2 size_best = {BEST_CHAR_WIDTH*BEST_LENGTH,(BEST_CHAR_WIDTH)*2};
	hud_best.add_component<Text>(size_best, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::GREY,
	}, TOP_LEFT+FONTOFFSET+BEST_OFFSET + vec2{BEST_LENGTH * BEST_CHAR_WIDTH/2,0}, BEST);

	// Coins
	GameObject hud_coin = scn.new_object(HUD_COINS);
	crepe::vec2 size_coin = {COINS_CHAR_WIDTH*COINS_LENGTH,(COINS_CHAR_WIDTH)*2};
	hud_coin.add_component<Text>(size_coin, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::YELLOW,
	}, TOP_LEFT+FONTOFFSET+COINS_OFFSET + vec2{COINS_LENGTH * COINS_CHAR_WIDTH/2,0}, COINS);

	// Fps
	GameObject hud_fps = scn.new_object(HUD_FPS);
	crepe::vec2 size_fps = {FPS_CHAR_WIDTH*FPS_LENGTH,(FPS_CHAR_WIDTH)*2};
	hud_fps.add_component<Text>(size_fps, FONT,Text::Data{
		.world_space = false,
		.text_color = Color::GREEN,
	}, TOP_LEFT+FONTOFFSET+FPS_OFFSET + vec2{FPS_LENGTH * FPS_CHAR_WIDTH/2,0}, FPS);
}
