#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

#include "../Config.h"

struct MissileSpawnEvent : public crepe::Event {};

class MissileSpawnEventHandler : public crepe::Script {
private:
	static constexpr int MISSILE_OFFSET = VIEWPORT_X;
	static constexpr int MIN_RANGE = -150;
	static constexpr int MAX_RANGE = 150;

public:
	void init();
	bool on_event(const MissileSpawnEvent & ev);
};
