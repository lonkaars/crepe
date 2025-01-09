#pragma once

#include <chrono>
#include <crepe/api/Event.h>
#include <crepe/api/Script.h>
class PlayerScript : public crepe::Script {
public:
	void init();
	void fixed_update(crepe::duration_t dt);

private:
	bool on_collision(const crepe::CollisionEvent & ev);
	// bool on_key_up(const crepe::KeyReleaseEvent& ev);
	void shoot(const crepe::vec2 & location, float angle);

private:
	int prev_anim = 0;
	bool gravity_mode = true;
	bool fall_direction = false;
	std::chrono::time_point<std::chrono::steady_clock> last_fired;
	std::chrono::time_point<std::chrono::steady_clock> last_switched;
	std::chrono::duration<float> shot_delay = std::chrono::duration<float>(0.5);
	std::chrono::duration<float> switch_delay = std::chrono::duration<float>(0.01);
	int current_jetpack_sound = 0;
};
