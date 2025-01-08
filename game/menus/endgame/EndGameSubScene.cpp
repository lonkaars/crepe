
#include "EndGameSubScene.h"
#include "../../Config.h"
#include "../ButtonSubScene.h"
#include "../FloatingWindowSubScene.h"
#include "EndGameSubScript.h"
#include "types.h"
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Text.h>
#include <string>

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
			// .script_type = ButtonSubScene::ScriptSelect::MAINMENU,
			.button_type = ButtonSubScene::ButtonSelect::BACK,
			.scale = 0.6,
			.worldspace = false,
			.tag = TAG,
			.sorting_layer_offset = 20,
		}
	);
}
