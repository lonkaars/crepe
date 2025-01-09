#pragma once
#include "types.h"

#include <crepe/api/Config.h>

static const crepe::Config ENGINE_CONFIG {
	.log {
		.level = crepe::Log::Level::DEBUG,
	},
	.window_settings {
		.window_title = "Jetpack joyride clone",
	},
};

static constexpr int SORT_IN_LAY_BACK_BACKGROUND = 3; // For all scenes
static constexpr int SORT_IN_LAY_BACKGROUND = 4; // For all scenes
static constexpr int SORT_IN_LAY_FORE_BACKGROUND = 5; // For all scenes
static constexpr int SORT_IN_LAY_PARTICLES_BACKGROUND = 6; // For all scenes
static constexpr int SORT_IN_LAY_COINS = 7; // Only for GameScene
static constexpr int SORT_IN_LAY_OBSTACLES = 8; // Only for GameScene
static constexpr int SORT_IN_LAY_WORKERS_BACK = 9; // Only for GameScene
static constexpr int SORT_IN_LAY_PLAYER = 10; // Only for GameScene
static constexpr int SORT_IN_LAY_WORKERS_FRONT = 12; // Only for GameScene
static constexpr int SORT_IN_LAY_PARTICLES_FOREGROUND = 15; // Only for GameScene

static constexpr int COLL_LAY_BOT_TOP = 1; // Only for GameScene
static constexpr int COLL_LAY_BOT_LOW = 2; // Only for GameScene
static constexpr int COLL_LAY_BOT_HIGH = 3; // Only for GameScene
static constexpr int COLL_LAY_PLAYER = 4; // Only for GameScene
static constexpr int COLL_LAY_WALL_FRAGS = 5; // Only for GameScene
static constexpr int COLL_LAY_ZAPPER = 6; // Only for GameScene
static constexpr int COLL_LAY_LASER = 7; // Only for GameScene
static constexpr int COLL_LAY_MISSILE = 8; // Only for GameScene
static constexpr int COLL_LAY_BULLET = 9; // Only for GameScene
static constexpr int COLL_LAY_ENEMY = 10; // Only for GameScene
static constexpr int COLL_LAY_PLAYER_BULLET = 11; // Only for GameScene

static constexpr float GAME_HEIGHT = 800; // In game units
static constexpr float HALLWAY_HEIGHT = 475; // In game units

static constexpr float VIEWPORT_X = 1100; // In game units
// 'GAME_HEIGHT' (below) should be replaced by '500' when game development is finished
static constexpr float VIEWPORT_Y = 500; // In game units

// Font settings
static constexpr const char * FONT = "Jetpackia";
static constexpr crepe::vec2 FONTOFFSET = {0, 0};

// Amount of coins in game
static constexpr const char * TOTAL_COINS_GAME = "total_coins_game";

// Amount of coins in current run
static constexpr const char * TOTAL_COINS_RUN = "total_coins_run";

// Distance
static constexpr const char * DISTANCE_GAME = "distance_game";
static constexpr const char * DISTANCE_RUN = "distance_run";

// Player config
static constexpr const char * PLAYER_NAME = "player";
static constexpr int PLAYER_SPEED = 7500; // In game units
static constexpr int PLAYER_GRAVITY_SCALE = 60; // In game units

static constexpr const char * CAMERA_NAME = "camera";
// Jetpack particles
static constexpr const char * JETPACK_PARTICLES = "jetpack_particles";
