#pragma once
#include <crepe/types.h>

static constexpr crepe::vec2 TOP_LEFT = {-530,-230};
static constexpr const char* HUD_DISTANCE = "hud_distance";
static constexpr const char* HUD_BEST = "hud_best";	
static constexpr const char* HUD_COINS = "hud_coins";	
static constexpr const char* HUD_FPS = "hud_fps";	

// Distance
static constexpr const char* DISTANCE_PLACEHOLDER = "0000m";
static constexpr const char* DISTANCE_UNIT = "m";
static constexpr int DISTANCE_LENGTH = 5;
static constexpr float DISTANCE_CHAR_WIDTH = 12;
static constexpr float STEP_SIZE_DISTANCE = 100;

// BEST
static constexpr const char* BEST = "BEST:";
static constexpr int BEST_LENGTH = 5;
static constexpr float BEST_CHAR_WIDTH = 10;
static constexpr crepe::vec2 BEST_OFFSET = {0,25};

// COINS
static constexpr const char* COINS = "0000";
static constexpr int COINS_LENGTH = 4;
static constexpr float COINS_CHAR_WIDTH = 10;
static constexpr crepe::vec2 COINS_OFFSET = {0,50};

// FPS
static constexpr const char* FPS = "00";
static constexpr int FPS_LENGTH = 2;
static constexpr float FPS_CHAR_WIDTH = 10;
static constexpr crepe::vec2 FPS_OFFSET = {1030,0};
	