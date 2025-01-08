#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

#include "../Config.h"

struct MissileSpawnEvent : public crepe::Event {};

class MissileSpawnEventHandler : public crepe::Script {
private:
	static constexpr int MISSILE_OFFSET = VIEWPORT_X;
	static constexpr int RANGE = GAME_HEIGHT / 4;
	static constexpr int MIN_RANGE = -RANGE;
	static constexpr int MAX_RANGE = RANGE;

public:
	void init();
	bool on_event(const MissileSpawnEvent & ev);
};
