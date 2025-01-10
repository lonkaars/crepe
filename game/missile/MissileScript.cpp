#include "MissileScript.h"
#include "../Config.h"
#include "Collider.h"
#include "api/BehaviorScript.h"
#include "api/CircleCollider.h"
#include "api/Rigidbody.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/Transform.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/types.h>

#include <cmath>
#include <crepe/api/AI.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Sprite.h>

using namespace std;
using namespace crepe;

void MissileScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
	this->seeking_disabled = false;
}
void MissileScript::kill_missile() {
	auto animations = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();
	auto collider = this->get_component<CircleCollider>();
	auto & fly_sound = this->get_components<AudioSource>().front().get();
	auto & this_script = this->get_components<BehaviorScript>().front().get();

	animations[0].get().active = false;
	animations[1].get().active = false;
	animations[2].get().active = true;
	sprites[0].get().active = false;
	sprites[1].get().active = false;
	sprites[2].get().active = true;
	collider.active = false;
	this_script.active = false;
	this->seeking_disabled = false;

	fly_sound.stop();
}
void MissileScript::activate() {
	auto anim = this->get_components<Animator>();
	auto sprites = this->get_components<Sprite>();

	anim[0].get().active = true;
	anim[1].get().active = true;
	anim[2].get().stop();
	//anim[3].get().active = true;

	sprites[0].get().active = true;
	sprites[1].get().active = true;
	sprites[2].get().active = false;
	//sprites[3].get().active = true;
}

bool MissileScript::on_collision(const CollisionEvent & ev) {
	auto & explosion_sound = this->get_components<AudioSource>().back().get();

	this->kill_missile();
	explosion_sound.play();

	return false;
}

bool MissileScript::is_in_x_range(const Transform & missile, const Transform & player) {
	return fabs(missile.position.x - player.position.x) <= this->X_RANGE;
}

void MissileScript::fixed_update(crepe::duration_t dt) {
	auto & explosion_anim = this->get_components<Animator>().back().get();
	auto & missile = this->get_component<Transform>();
	auto & m_ai = this->get_component<AI>();

	const auto & player = this->get_components_by_name<Transform>("player").front().get();
	const auto & cam = this->get_components_by_name<Transform>("camera").front().get();
	const auto & velocity = this->get_component<Rigidbody>().data.linear_velocity;

	if (missile.position.x < (cam.position.x - VIEWPORT_X / 1.8)) {
		this->kill_missile();
		return;
	}

	// check if animation is at the end
	if (explosion_anim.data.row == 7) {
		this->activate();
		this->seeking_disabled = false;
	}

	if (this->seeking_disabled) {
		m_ai.seek_off();
	} else {
		m_ai.seek_target = player.position;
		m_ai.seek_on();

		if (is_in_x_range(missile, player)) {
			this->seeking_disabled = true;
			m_ai.seek_off();
		}
	}

	vec2 angle_pos = velocity;
	float angle = atan2(angle_pos.y, angle_pos.x) * (180 / M_PI);

	missile.rotation = angle;
	missile.position += velocity * dt.count();
}
