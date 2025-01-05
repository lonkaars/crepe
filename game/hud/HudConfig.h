#pragma once
#include "types.h"

static constexpr crepe::vec2 TOP_LEFT = {-500,-380};
static constexpr const char* HUD_DISTANCE = "hud_distance";
static constexpr const char* HUD_BEST = "hud_best";	
static constexpr const char* HUD_COINS = "hud_coins";	

// Distance
static constexpr const char* DISTANCE_PLACEHOLDER = "0000m";
static constexpr const char* DISTANCE_UNIT = "m";
static constexpr int DISTANCE_LENGTH = 5;
static constexpr float DISTANCE_WIDTH = 60;
static constexpr float STEP_SIZE_DISTANCE = 100;

// BEST
static constexpr const char* BEST = "BEST:";
static constexpr int BEST_LENGTH = 5;
static constexpr float BEST_WIDTH = 40;
static constexpr crepe::vec2 BEST_OFFSET = {0,25};

// COINS
static constexpr const char* COINS = "0000";
static constexpr int COINS_LENGTH = 4;
static constexpr float COINS_WIDTH = 40;
static constexpr crepe::vec2 COINS_OFFSET = {0,50};

	