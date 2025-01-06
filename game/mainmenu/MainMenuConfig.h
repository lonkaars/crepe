#pragma once
#include "types.h"
#include <string>


struct MainMenuConfig {
	//generic menu config
	static constexpr unsigned int STARTING_SORTING_IN_LAYER = 7;
	static constexpr const char* CAMERA_NAME = "camera";
	//main menu config
	static constexpr float STARTMAP_OFFSET = 50;
	static constexpr crepe::vec2 MENU_OFFSET = {0,0};
	static constexpr float MENU_BUTTON_SPACING = 10;
	static constexpr const char* MENU_BUTTON_NAME = "menu_button_background";
	static constexpr crepe::vec2 MENU_OFFSET_BUTTON = {-400,-200};
	static constexpr crepe::vec2 MENU_OFFSET_BUTTON_BACKGROUND = {-400,0};
	static constexpr const char* MENU_INFO_TAG = "menu_info";
	static constexpr crepe::vec2 MENU_OFFSET_INFO = {350,-365};
	static constexpr crepe::vec2 MENU_OFFSET_INFO_BACKGROUND = {350,-365}; //375
	//Scene names
	static constexpr const char* START_SCENE = "scene1";
	static constexpr const char* PREVIEW_SCENE = "scene1";
	static constexpr const char* SHOP_SCENE = "shopmenu";
	static constexpr const char* MAINMENU_SCENE = "mainmenu";
	//Moving to new scene (Start and Preview)
	static constexpr float SLOW_DOWN = 200;
	static constexpr float END = 300;
	static constexpr float VELOCITY_MAX = 200;
	static constexpr float VELOCITY_STEP = 200;
	static constexpr float VELOCITY_INFO_UP = 40;
	//button config
	static constexpr crepe::vec2 LARGE_OVERLAY_SIZE = {250,100};
	static constexpr crepe::vec2 SMALL_OVERLAY_SIZE_RIGHT = {150,100};
	static constexpr crepe::vec2 SMALL_OVERLAY_SIZE_LEFT = {50,100};
	static constexpr crepe::vec2 SIDE_PANEL_SIZE = {50,150};
	static constexpr crepe::vec2 ICON_SIZE = {50,50};
	
};

