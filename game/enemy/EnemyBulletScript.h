#pragma once
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Script.h>

class EnemyBulletScript : public crepe::Script{
	public:
		void init() override;
		void fixed_update(crepe::duration_t dt) override;
		bool on_collide(const crepe::CollisionEvent& e);
		void despawn_bullet();
};
