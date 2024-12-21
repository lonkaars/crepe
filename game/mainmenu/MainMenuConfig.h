#pragma once
#include "types.h"
#include <string>

struct MainMenuConfig {
	//generic menu config
	static constexpr unsigned int STARTING_SORTING_IN_LAYER = 7;
	static constexpr const char* CAMERA_NAME = "camera";
	static constexpr const char* START_SCENE = "scene1";
	//main menu config
	static constexpr float STARTMAP_OFFSET = 50;
	static constexpr crepe::vec2 MENU_OFFSET = {-400,-200};
	static constexpr float MENU_BUTTON_SPACING = 10;
	static constexpr crepe::vec2 MENU_OFFSET_BACKGROUND = {0,+200};

	//button config
	static constexpr const char* FONT = "Garuda";
	static constexpr crepe::vec2 FONTOFFSET = {0,0};
	static constexpr crepe::vec2 LARGE_OVERLAY_SIZE = {250,100};
	static constexpr crepe::vec2 SIDE_PANEL_SIZE = {50,150};
};

