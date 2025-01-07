#pragma once

static constexpr int SORT_IN_LAY_BACK_BACKGROUND = 3; // For all scenes
static constexpr int SORT_IN_LAY_BACKGROUND = 4; // For all scenes
static constexpr int SORT_IN_LAY_FORE_BACKGROUND = 5; // For all scenes
static constexpr int SORT_IN_LAY_PARTICLES_BACKGROUND = 6; // For all scenes
static constexpr int SORT_IN_LAY_OBSTACLES = 8; // Only for GameScene
static constexpr int SORT_IN_LAY_PLAYER = 10; // Only for GameScene
static constexpr int SORT_IN_LAY_WORKERS = 12; // Only for GameScene
static constexpr int SORT_IN_LAY_PARTICLES_FOREGROUND = 15; // Only for GameScene

static constexpr int COLL_LAY_BOT_TOP = 1; // Only for GameScene
static constexpr int COLL_LAY_BOT_LOW = 2; // Only for GameScene
static constexpr int COLL_LAY_BOT_HIGH = 3; // Only for GameScene
static constexpr int COLL_LAY_PLAYER = 4; // Only for GameScene
static constexpr int COLL_LAY_WALL_FRAGS = 5; // Only for GameScene
static constexpr int COLL_LAY_ZAPPER = 6; // Only for GameScene
static constexpr int COLL_LAY_LASER = 7; // Only for GameScene
static constexpr int COLL_LAY_MISSILE = 8; // Only for GameScene

static constexpr int GAME_HEIGHT = 800; // In game units

static constexpr int VIEWPORT_X = 1100; // In game units
// 'GAME_HEIGHT' (below) should be replaced by '500' when game development is finished
static constexpr int VIEWPORT_Y = GAME_HEIGHT; // In game units

static constexpr int PLAYER_SPEED = 7500; // In game units
static constexpr int PLAYER_GRAVITY_SCALE = 60; // In game units
