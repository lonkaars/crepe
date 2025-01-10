#pragma once
#include <chrono>
#include <crepe/api/Camera.h>
#include <crepe/api/Event.h>
#include <crepe/api/Script.h>
#include <random>
struct SpawnEnemyEvent : public crepe::Event {
	float speed = 0;
	int column = 0;
};
class EnemyScript : public crepe::Script {
public:
	EnemyScript();
	void init() override;
	void fixed_update(crepe::duration_t dt) override;
	void shoot(const crepe::vec2 & position);
	bool on_collide(const crepe::CollisionEvent & collisionData);
	void despawn_enemy();
	bool spawn_enemy(const SpawnEnemyEvent & e);
	void death();
	void set_hit_blink(bool status);

private:
	std::random_device rd;
	std::default_random_engine engine;
	bool alive = false;
	bool spawned = false;
	float speed = 50;
	int health = 2;
	const float MIN_SPEED = 20;
	const float MAX_SPEED = 150;
	const float MAX_DISTANCE = 200;
	std::chrono::time_point<std::chrono::steady_clock> last_fired;
	std::chrono::time_point<std::chrono::steady_clock> last_hit;
	std::chrono::duration<float> shot_delay = std::chrono::duration<float>(0);
	std::chrono::duration<float> blink_time = std::chrono::duration<float>(0.1);
};
