

#include "CollisionScript.h"
#include "api/Animator.h"
#include "api/BehaviorScript.h"
#include "api/Rigidbody.h"
#include "api/Sprite.h"
#include "api/Transform.h"

#include <crepe/system/CollisionSystem.h>

using namespace crepe;



void MissileCollisionScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}

bool MissileCollisionScript::on_collision(const CollisionEvent & ev){
	if (!this->alive) return true;
	auto animations = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();

	for (auto & sprite : sprites) {
		sprite.get().active ^= 1;
	}

	for (auto & anim  : animations) {
		anim.get().active ^= 1;
	}

	animations[2].get().set_anim(0);
	animations[2].get().play();
	this->alive = false;
	return true;
}

void MissileCollisionScript::fixed_update(duration_t dt) {
	if (!this->alive) return;

	auto & rb = this->get_component<Rigidbody>();
	auto & transform = this->get_component<Transform>();

	transform.position += rb.data.linear_velocity * dt.count();
}
