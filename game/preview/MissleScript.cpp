#include "MissleScript.h"
#include "api/Animator.h"
#include "api/AudioSource.h"
#include "api/Transform.h"
#include "system/CollisionSystem.h"
#include "types.h"

#include <cmath>
#include <crepe/api/AI.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Sprite.h>
#include <iostream>

using namespace std;
using namespace crepe;

void MissleScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}


bool MissleScript::on_collision(const CollisionEvent & ev){
	auto animations = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();
	auto & fly_sound  = this->get_components<AudioSource>().front().get();
	auto & explosion_sound  = this->get_components<AudioSource>().back().get();
	auto & this_script = this->get_components<BehaviorScript>().back().get();
	this_script.active = false;

	fly_sound.stop();
	fly_sound.active = false;

	for (auto & sprite : sprites) {
		sprite.get().active ^= 1;
	}

	for (auto & anim  : animations) {
		anim.get().active ^= 1;
	}

	explosion_sound.play();
	return false;
}

void MissleScript::fixed_update(crepe::duration_t dt) {
	auto anim = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();
	const auto & player = this->get_components_by_name<Transform>("player").front().get();
	const auto & rb = this->get_component<Rigidbody>();
	auto & missile = this->get_component<Transform>();
	auto & m_ai = this->get_component<AI>();

	if (anim[2].get().data.row == 7) {
		anim[0].get().active = true;
		anim[1].get().active = true;
		anim[2].get().active = false;
		sprites[0].get().active = true;
		sprites[1].get().active = true;
		sprites[2].get().active = false;
	}

	m_ai.seek_target = player.position;
	m_ai.seek_on();

	vec2 angle_pos = rb.data.linear_velocity;
	float angle = atan2(angle_pos.y, angle_pos.x) * (180 / M_PI);

	missile.rotation = angle;
	missile.position += rb.data.linear_velocity * dt.count();
}
