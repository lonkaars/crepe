#include "ButtonSubScene.h"
#include "ButtonNextMainMenuSubScript.h"
#include "ButtonReplaySubScript.h"
#include "ButtonSetMainMenuSubScript.h"
#include "ButtonSetShopSubScript.h"
#include "ButtonShowCreditsSubScript.h"
#include "IButtonScript.h"
#include "MenusConfig.h"

#include "../preview/PreviewReplaySubScript.h"
#include "../preview/PreviewStartRecSubScript.h"
#include "../preview/PreviewStopRecSubScript.h"
#include "api/Asset.h"
#include "mainmenu/ButtonTransitionPreviewSubScript.h"

#include "../Config.h"
#include "mainmenu/CreditsSubScript.h"
#include "menus/shop/ButtonBuySelectBubbleScript.h"
#include "menus/shop/ButtonBuySelectBulletScript.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Button.h>
#include <crepe/api/Color.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>

using namespace crepe;
using namespace std;

void ButtonSubScene::create(Scene & scn, const Data & data) {
	GameObject button_object
		= scn.new_object("button", data.tag, data.position, 0, data.scale);
	this->set_button_overlay(button_object, data);
	this->btn_text(button_object, data);
	this->set_script(button_object, data);
	this->set_icon(button_object, data);
}

void ButtonSubScene::btn_text(crepe::GameObject & button_object, const Data & data) {

	crepe::vec2 size = {data.text_width, (data.text_width / data.text.size()) * 2};
	button_object.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = data.worldspace,
			.text_color = Color::WHITE,
		},
		data.text_offset + FONTOFFSET, data.text
	);
}

void ButtonSubScene::set_script(crepe::GameObject & button_object, const Data & data) {
	switch (data.script_type) {
		case ScriptSelect::PREVIEW:
			button_object.add_component<BehaviorScript>()
				.set_script<ButtonTransitionPreviewSubScript>();
			break;
		case ScriptSelect::SHOP:
			button_object.add_component<BehaviorScript>().set_script<ButtonSetShopSubScript>();
			break;
		case ScriptSelect::MAINMENU:
			button_object.add_component<BehaviorScript>()
				.set_script<ButtonSetMainMenuSubScript>();
			break;
		case ScriptSelect::NEXT:
			button_object.add_component<BehaviorScript>()
				.set_script<ButtonNextMainMenuSubScript>();
			break;
		case ScriptSelect::REPLAY:
			button_object.add_component<BehaviorScript>().set_script<ButtonReplaySubScript>();
			break;
		case ScriptSelect::CREDITS_BACK:
			button_object.add_component<BehaviorScript>().set_script<CreditsSubScript>(data.tag
			);
			break;
		case ScriptSelect::CREDITS_SHOW:
			button_object.add_component<BehaviorScript>()
				.set_script<ButtonShowCreditsSubScript>();
			break;
		case ScriptSelect::PREVIEW_REPLAY:
			button_object.add_component<BehaviorScript>()
				.set_script<PreviewReplaySubScript>();
			break;
		case ScriptSelect::PREVIEW_START:
			button_object.add_component<BehaviorScript>()
				.set_script<PreviewStartRecSubScript>();
			break;
		case ScriptSelect::PREVIEW_STOP:
		button_object.add_component<BehaviorScript>()
				.set_script<PreviewStopRecSubScript>();
			break;
		case ScriptSelect::SHOP_BULLET:
		button_object.add_component<BehaviorScript>()
				.set_script<ButtonBuySelectBulletScript>();
			break;
		case ScriptSelect::SHOP_BUBBLE:
		button_object.add_component<BehaviorScript>()
				.set_script<ButtonBuySelectBubbleScript>();
			break;
		case ScriptSelect::NONE:
			button_object.add_component<BehaviorScript>().set_script<IButtonScript>();
			break;
	}
}

void ButtonSubScene::set_icon(crepe::GameObject & button_object, const Data & data) {
	switch (data.icon_type) {
		case IconSelect::SHOP:
			button_object.add_component<Sprite>(
				Asset("asset/ui/buttonCoinsSmall.png"),
				Sprite::Data {
					.sorting_in_layer
					= STARTING_SORTING_IN_LAYER + 3 + data.sorting_layer_offset,
					.size = ICON_SIZE,
					.position_offset = data.icon_offset,
					.world_space = data.worldspace,
				}
			);
			break;
		case IconSelect::COINS:
			button_object.add_component<Sprite>(
				Asset("asset/ui/buttonCoinsSmall.png"),
				Sprite::Data {
					.sorting_in_layer
					= STARTING_SORTING_IN_LAYER + 3 + data.sorting_layer_offset,
					.size = ICON_SIZE,
					.position_offset = data.icon_offset,
					.world_space = data.worldspace,
				}
			);
			break;
		case IconSelect::NONE:
			break;
	}
}

void ButtonSubScene::set_button_overlay(crepe::GameObject & button_object, const Data & data) {
	switch (data.button_type) {
		case ButtonSelect::LARGE:
			this->large_btn_overlay(button_object, data);
			break;
		case ButtonSelect::BACK:
			this->back_btn_overlay(button_object, data);
			break;
		case ButtonSelect::NEXT:
			this->next_btn_overlay(button_object, data);
			break;
	}
}

void ButtonSubScene::large_btn_overlay(crepe::GameObject & button_object, const Data & data) {
	button_object.add_component<Sprite>(
		Asset("asset/ui/buttonBacking.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1 + data.sorting_layer_offset,
			.size = LARGE_OVERLAY_SIZE,
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Button>(LARGE_OVERLAY_SIZE, Button::Data {});
	if (!data.color_side) return;
	this->btn_color_side(button_object, SIDE_PANEL_OFFSET, data);
}

void ButtonSubScene::back_btn_overlay(crepe::GameObject & button_object, const Data & data) {
	button_object.add_component<Sprite>(
		Asset("asset/ui/backbuttonright.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1 + data.sorting_layer_offset,
			.size = SMALL_OVERLAY_SIZE_RIGHT,
			.position_offset = {20, 0},
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Sprite>(
		Asset("asset/ui/backbuttonleft.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1 + data.sorting_layer_offset,
			.size = SMALL_OVERLAY_SIZE_LEFT,
			.position_offset = {-80, 0},
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Button>(
		vec2 {
			SMALL_OVERLAY_SIZE_LEFT.x + SMALL_OVERLAY_SIZE_RIGHT.x, SMALL_OVERLAY_SIZE_LEFT.y
		},
		Button::Data {}
	);
}

void ButtonSubScene::next_btn_overlay(crepe::GameObject & button_object, const Data & data) {
	button_object.add_component<Sprite>(
		Asset("asset/ui/backbuttonright.png"),
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1 + data.sorting_layer_offset,
			.size = SMALL_OVERLAY_SIZE_RIGHT,
			.position_offset = {-20, 0},
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Sprite>(
		Asset("asset/ui/backbuttonleft.png"),
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1 + data.sorting_layer_offset,
			.size = SMALL_OVERLAY_SIZE_LEFT,
			.position_offset = {80, 0},
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Button>(
		vec2 {
			SMALL_OVERLAY_SIZE_LEFT.x + SMALL_OVERLAY_SIZE_RIGHT.x, SMALL_OVERLAY_SIZE_LEFT.y
		},
		Button::Data {}
	);
}

void ButtonSubScene::btn_color_side(
	crepe::GameObject & button_object, const vec2 & offset, const Data & data
) {
	Asset * selected;
	Asset blue = Asset("asset/ui/buttonSmallBlue.png");
	Asset orange = Asset("asset/ui/buttonSmallOrange.png");
	Asset purple = Asset("asset/ui/buttonSmallPurple.png");
	Asset yellow = Asset("asset/ui/buttonSmallYellow.png");
	switch (data.btn_side_color) {
		case ButtonSideColor::BLUE:
			selected = &blue;
			break;
		case ButtonSideColor::ORANGE:
			selected = &orange;
			break;
		case ButtonSideColor::PURPLE:
			selected = &purple;
			break;
		case ButtonSideColor::YELLOW:
			selected = &yellow;
			break;
		case ButtonSideColor::NONE:
			selected = &blue;
			break;
	}

	button_object.add_component<Sprite>(
		*selected,
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 2 + data.sorting_layer_offset,
			.size = SIDE_PANEL_SIZE,
			.position_offset = offset,
			.world_space = data.worldspace,
		}
	);
	button_object.add_component<Sprite>(
		*selected,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 2 + data.sorting_layer_offset,
			.size = SIDE_PANEL_SIZE,
			.position_offset = {-offset.x, offset.y},
			.world_space = data.worldspace,
		}
	);
}
