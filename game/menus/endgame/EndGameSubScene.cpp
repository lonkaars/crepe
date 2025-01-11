
#include "EndGameSubScene.h"
#include "EndGameSubScript.h"

#include "../../Config.h"
#include "../ButtonSubScene.h"
#include "../FloatingWindowSubScene.h"

#include <string>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Text.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void EndGameSubScene::create(Scene & scn) {

	const std::string TAG = "end_game_tag";
	GameObject script = scn.new_object("script");
	script.add_component<BehaviorScript>().set_script<EndGameSubScript>(TAG);

	// Window
	FloatingWindowSubScene window;
	window.create(
		scn,
		FloatingWindowSubScene::Data {
			.group_tag = TAG,
			.width = 500,
			.offset = {0, -50},
			.width_middle_offset = -2,
		}
	);

	// Titel
	const string TITEL_STRING = "GAME OVER";
	GameObject titel = scn.new_object("titel", TAG);
	crepe::vec2 size = {200, (200.0f / TITEL_STRING.size()) * 2};
	titel.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = false,
			.text_color = Color::WHITE,
		},
		vec2 {0, -207} + FONTOFFSET, TITEL_STRING
	);

	const float Y_SPACING = 50;
	const float Y_OFFSET = -100;

	// Gold gathered
	const string GOLD_STRING = "gold:0";
	GameObject gold = scn.new_object("gold_endgame", TAG);
	crepe::vec2 size_gold = {200, (200.0f / GOLD_STRING.size()) * 2};
	gold.add_component<Text>(
		size_gold, FONT,
		Text::Data {
			.world_space = false,
			.text_color = Color::GOLD,
		},
		vec2 {0, Y_OFFSET} + FONTOFFSET, GOLD_STRING
	);

	// Distance
	const string DISTANCE_STRING = "0M";
	GameObject distance = scn.new_object("distance_endgame", TAG);
	crepe::vec2 size_distance = {200, (200.0f / DISTANCE_STRING.size()) * 2};
	distance.add_component<Text>(
		size_distance, FONT,
		Text::Data {
			.world_space = false,
			.text_color = Color::WHITE,
		},
		vec2 {0, Y_SPACING + Y_OFFSET} + FONTOFFSET, DISTANCE_STRING
	);

	// Highscore
	const string HIGHSCORE_STRING = "NEW HIGHSCORE";
	GameObject highscore = scn.new_object("highscore_endgame", "highscore_tag_end");
	crepe::vec2 size_highscore = {200, (200.0f / HIGHSCORE_STRING.size()) * 2};
	highscore
		.add_component<Text>(
			size_highscore, FONT,
			Text::Data {
				.world_space = false,
				.text_color = Color::WHITE,
			},
			vec2 {0, Y_SPACING * 2 + Y_OFFSET} + FONTOFFSET, HIGHSCORE_STRING
		)
		.active
		= false;

	// Buttons
	vec2 button_position = {190, 190};
	ButtonSubScene button;
	button.create(
		scn,
		ButtonSubScene::Data {
			.text = "NEXT",
			.text_width = 100,
			.position = button_position,
			.script_type = ButtonSubScene::ScriptSelect::NEXT,
			.button_type = ButtonSubScene::ButtonSelect::NEXT,
			.scale = 0.6,
			.worldspace = false,
			.tag = TAG,
			.sorting_layer_offset = 20,
		}
	);

	button.create(
		scn,
		ButtonSubScene::Data {
			.text = "REPLAY",
			.text_width = 150,
			.position = {-button_position.x, button_position.y},
			.script_type = ButtonSubScene::ScriptSelect::REPLAY,
			.button_type = ButtonSubScene::ButtonSelect::BACK,
			.scale = 0.6,
			.worldspace = false,
			.tag = TAG,
			.sorting_layer_offset = 20,
		}
	);
}
