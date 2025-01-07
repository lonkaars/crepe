

#include "CollisionScript.h"
#include "api/Animator.h"
#include "api/AudioSource.h"
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
	auto animations = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();
	auto & explosion_sound  = this->get_components<AudioSource>().back().get();
	auto & this_script = this->get_components<BehaviorScript>().back().get();
	this_script.active = false;

	for (auto & sprite : sprites) {
		sprite.get().active ^= 1;
	}

	for (auto & anim  : animations) {
		anim.get().active ^= 1;
	}

	explosion_sound.play();
	return true;
}

void MissileCollisionScript::fixed_update(duration_t dt) {
	auto & rb = this->get_component<Rigidbody>();
	auto & transform = this->get_component<Transform>();

	transform.position += rb.data.linear_velocity * dt.count();
}
