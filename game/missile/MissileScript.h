#pragma once

#include <crepe/api/Script.h>

class MissileScript : public crepe::Script {
private:
	bool on_collision(const crepe::CollisionEvent & ev);

	bool seeking_disabled;

	// will be used to calculate when ai will be stopped
	static constexpr int X_RANGE = 90;
	bool is_in_x_range(const crepe::Transform & missile, const crepe::Transform & player);
	void kill_missile();
	void activate();

public:
	void init();
	void fixed_update(crepe::duration_t dt);
};
