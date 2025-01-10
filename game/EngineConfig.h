#pragma once

#include "Config.h"

#include <crepe/api/Config.h>

static const crepe::Config ENGINE_CONFIG {
	.log {
		.level = crepe::Log::Level::DEBUG,
	},
	.physics {
		// this division factor is now the amount of seconds it approximately takes to naturally
		// fall from the ceiling to floor
		.gravity = HALLWAY_HEIGHT / 0.5,
	},
	.window_settings {
		.window_title = "Jetpack joyride clone",
	},
};
