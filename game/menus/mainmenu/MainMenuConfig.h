#pragma once
#include <crepe/types.h>

//main menu config
static constexpr float STARTMAP_OFFSET = 50;
static constexpr crepe::vec2 MENU_OFFSET = {0, 0};
static constexpr float MENU_BUTTON_SPACING = 10;
static constexpr const char * MENU_BUTTON_NAME = "menu_button_background";
static constexpr crepe::vec2 MENU_OFFSET_BUTTON = {-400, -200};
static constexpr crepe::vec2 MENU_OFFSET_BUTTON_BACKGROUND = {-400, 0};
static constexpr const char * MENU_INFO_TAG = "menu_info";
static constexpr crepe::vec2 MENU_OFFSET_INFO = {350, -365};
static constexpr crepe::vec2 MENU_OFFSET_INFO_BACKGROUND = {350, -365}; //375
//Moving to new scene (Start and Preview)
static constexpr float SLOW_DOWN = 200;
static constexpr float END = 300;
static constexpr float VELOCITY_MAX = 200;
static constexpr float VELOCITY_STEP = 200;
static constexpr float VELOCITY_INFO_UP = 40;
