#include "BannerSubScene.h"
#include "MenusConfig.h"

#include "../Config.h"

#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Text.h>

using namespace crepe;
using namespace std;

void BannerSubScene::create(Scene & scn, const Data & data) {
	GameObject menu_banner = scn.new_object("menu_banner", "", {0, -414});
	menu_banner.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {1100, 88},
		}
	);
	menu_banner.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {1100, 66},
			.position_offset {0, 77},
		}
	);
	menu_banner.add_component<Sprite>(
		Asset("asset/ui/settings_container/banner_bottom.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 1,
			.size = {1100, 7},
			.position_offset {0, 113},
		}
	);
	crepe::vec2 size
		= {data.banner_title_width, (data.banner_title_width / data.banner_title.size()) * 2};

	menu_banner.add_component<Text>(
		size, FONT,
		Text::Data {
			.world_space = true,
			.text_color = Color::WHITE,
		},
		data.banner_title_offset + FONTOFFSET, data.banner_title
	);
}
