#pragma once

#include "Component.h"
#include "types.h"

namespace crepe {

class AI : public Component {
public:
	enum BehaviorType {
		NONE = 0x00000,
		SEEK = 0x00002,
		FLEE = 0x00004,
		ARRIVE = 0x00008,
		PATH_FOLLOW = 0x00010,
	};

public:
	AI(game_object_id_t id, float max_force);

	bool on(BehaviorType behavior) const { return (flags & behavior) == behavior; }
	void seek_on() { flags |= SEEK; }
	void seek_off() {
		if (on(SEEK)) flags ^= SEEK;
	}
	void flee_on() { flags |= FLEE; }
	void flee_off() {
		if (on(FLEE)) flags ^= FLEE;
	}
	void arrive_on() { flags |= ARRIVE; }
	void arrive_off() {
		if (on(ARRIVE)) flags ^= ARRIVE;
	}
	void path_follow_on() { flags |= PATH_FOLLOW; }
	void path_follow_off() {
		if (on(PATH_FOLLOW)) flags ^= PATH_FOLLOW;
	}

public:
	float max_force;

	// The target to seek or arrive at
	vec2 seek_target;
	// The target to flee from
	vec2 flee_target;
	// The distance at which the entity will start to flee from the target
	float square_flee_panic_distance = 100.0f * 100.0f;
	// The deceleration rate for the arrive behavior (higher values will make the entity decelerate faster (less overshoot))
	float arrive_deceleration = 2.0f;

private:
	int flags = 0;
};

} // namespace crepe
