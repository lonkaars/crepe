#pragma once

#include "util/OptionalRef.h"
#include <chrono>
#include <crepe/api/Config.h>
#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

class PlayerScript : public crepe::Script {
public:
	void init();
	void fixed_update(crepe::duration_t dt);

private:
	bool on_collision(const crepe::CollisionEvent & ev);
	bool on_key_down(const crepe::KeyPressEvent & ev);
	bool on_key_up(const crepe::KeyReleaseEvent & ev);
	// bool on_key_up(const crepe::KeyReleaseEvent& ev);
	void shoot(const crepe::vec2 & location, float angle);
	void help_kick(const crepe::vec2 & direction);

private:
	int prev_anim = 0;
	std::chrono::time_point<std::chrono::steady_clock> last_fired;
	std::chrono::duration<float> shot_delay = std::chrono::duration<float>(0.5);

	int current_jetpack_sound = 0;

	float & engine_gravity = crepe::Config::get_instance().physics.gravity;
	crepe::OptionalRef<crepe::Rigidbody> body;
};
