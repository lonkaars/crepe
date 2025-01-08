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
	void shoot(const crepe::vec2 & position, float angle);
	bool on_collide(const crepe::CollisionEvent & collisionData);
	void despawn_enemy();
	bool spawn_enemy(const SpawnEnemyEvent & e);

private:
	std::random_device rd;
	std::default_random_engine engine;
	bool alive = false;
	float speed = 50;
	const float MIN_SPEED = 10;
	const float MAX_SPEED = 130;
	const float MAX_DISTANCE = 100;
	std::chrono::time_point<std::chrono::steady_clock> last_fired;
	std::chrono::duration<float> shot_delay = std::chrono::duration<float>(0);
};
