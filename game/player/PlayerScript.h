#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

class PlayerScript : public crepe::Script {
public:
	void init();
	void fixed_update(crepe::duration_t dt);
	
private:
	bool on_collision(const crepe::CollisionEvent & ev);
	// bool on_key_up(const crepe::KeyReleaseEvent& ev);
	void shoot(const crepe::vec2& location,float angle);
private:
	int prev_anim = 0;
};
