
#include "CreditsSubScene.h"
#include "CreditsSubScript.h"

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

void CreditsSubScene::create(Scene & scn) {

	const std::string TAG = "credits_tag";
	GameObject script = scn.new_object("script");
	script.add_component<BehaviorScript>().set_script<CreditsSubScript>(TAG);

	// Window
	FloatingWindowSubScene window;
	window.create(
		scn,
		FloatingWindowSubScene::Data {
			.group_tag = TAG,
			.width = 500,
			.offset = {150, -50},
			.width_middle_offset = -2,
		}
	);

	// Titel
	const string TITEL_STRING = "Credits";
	GameObject titel = scn.new_object("titel", TAG);
	crepe::vec2 size = {200, (200.0f / TITEL_STRING.size()) * 2};
	titel.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = false,
			.text_color = Color::WHITE,
		},
		vec2 {150, -207} + FONTOFFSET, TITEL_STRING
	);

	// Buttons
	vec2 button_position = {190, 190};
	ButtonSubScene button;
	button.create(
		scn,
		ButtonSubScene::Data {
			.text = "Back",
			.text_width = 150,
			.position = {-button_position.x+150, button_position.y},
			.script_type = ButtonSubScene::ScriptSelect::CREDITS_BACK,
			.button_type = ButtonSubScene::ButtonSelect::BACK,
			.scale = 0.6,
			.worldspace = false,
			.tag = TAG,
			.sorting_layer_offset = 20,
		}
	);
}
