#pragma once

#include "example/menu/Menu.h"
#include "types.h"
#include <crepe/api/Scene.h>

class MainMenuButton {
public:
	MainMenuButton(Scene0& from_scene);
private:
	Scene0& scene;
private:
	void place_btn();
	void place_btn_preview(const vec2 &position,const vec2& size);
private:
	// Sprite layer
	static constexpr int STARTING_LAYER = 1;
	// Amount of buttons
	static constexpr int BTN_AMOUNT = 10;
	// Determines x coordinates
	static constexpr int BTN_OFFSET_COLUM = -950;
	static constexpr int BTN_WITDH_COLUM = 150;
	// Determines y coordinates
	static constexpr int BTN_START_ROW = 100;
	static constexpr int BTN_END_ROW = 1200;
	static constexpr int BTN_SPACING_ROW = 8;
};
