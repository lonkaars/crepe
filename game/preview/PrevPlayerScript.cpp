#include "PrevPlayerScript.h"

#include "../missile/SpawnEvent.h"

#include <crepe/api/AudioSource.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;

bool PrevPlayerScript::key_pressed(const KeyPressEvent & ev) {
	switch (ev.key) {
		case Keycode::A:
			this->get_component<Rigidbody>().data.linear_velocity.x = -move_speed;
			this->body->data.flip = {true, false};
			this->head->data.flip = {true, false};
			break;
		case Keycode::D:
			this->get_component<Rigidbody>().data.linear_velocity.x = move_speed;
			this->body->data.flip = {false, false};
			this->head->data.flip = {false, false};
			break;
		case Keycode::D0:
			this->body_anim->set_anim(0);
			this->head_anim->set_anim(0);
			break;
		case Keycode::D1:
			this->body_anim->set_anim(1);
			this->head_anim->set_anim(1);
			break;
		case Keycode::D2:
			this->body_anim->set_anim(2);
			this->head_anim->set_anim(2);
			break;
		case Keycode::D3:
			this->body_anim->set_anim(3);
			this->head_anim->set_anim(3);
			break;
		case Keycode::D4:
			this->body_anim->set_anim(4);
			this->head_anim->set_anim(4);
			break;
		case Keycode::D5:
			this->body_anim->set_anim(5);
			this->head_anim->set_anim(5);
			break;
		case Keycode::D6:
			this->body_anim->set_anim(6);
			this->head_anim->set_anim(6);
			break;
		case Keycode::D7:
			this->body_anim->set_anim(7);
			this->head_anim->set_anim(7);
			break;
		case Keycode::LEFT:
			this->get_component<Transform>().rotation += 10;
			break;
		case Keycode::RIGHT:
			this->get_component<Transform>().rotation -= 10;
			break;
		case Keycode::UP:
			this->head->data.position_offset += 10;
			break;
		case Keycode::DOWN:
			this->head->data.position_offset -= 10;
			break;
		case Keycode::P:
			this->get_component<AudioSource>().active = true;
			break;
		case Keycode::J:
			this->get_components_by_name<Transform>("camera").front().get().position.x
				-= move_speed;
			break;
		case Keycode::K:
			this->get_components_by_name<Transform>("camera").front().get().position.y
				-= move_speed;
			break;
		case Keycode::L:
			this->get_components_by_name<Transform>("camera").front().get().position.x
				+= move_speed;
			break;
		case Keycode::I:
			this->get_components_by_name<Transform>("camera").front().get().position.y
				+= move_speed;
			break;
		case Keycode::M:
			trigger_event<MissileSpawnEvent>(MissileSpawnEvent {});
			break;
		default:
			break;
	}
	return false;
}

void PrevPlayerScript::init() {
	this->rb = get_component<Rigidbody>();

	auto animations = this->get_components<Animator>();
	body_anim = animations[0];
	head_anim = animations[1];

	auto sprites = this->get_components<Sprite>();
	body = sprites[0];
	head = sprites[1];

	subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		return this->key_pressed(ev);
	});
	subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		if (ev.repeat) return false;
		return this->on_key_down(ev);
	});
	subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent & ev) -> bool {
		return this->on_key_up(ev);
	});
};

void PrevPlayerScript::fixed_update(crepe::duration_t dt) {
	if (this->get_key_state(Keycode::SPACE)) {
		this->rb->add_force_linear(
			vec2(0, -1) * (engine_gravity * PLAYER_GRAVITY_SCALE * dt.count())
		);
	}

	auto & savemgr = this->get_save_manager();
	const auto & pos = this->get_component<Transform>().position;

	savemgr.set("player_x", pos.x);
	savemgr.set("player_y", pos.y);
};

bool PrevPlayerScript::on_key_down(const KeyPressEvent & ev) {
	if (ev.key == Keycode::SPACE) {
		const vec2 UP = {0, -1};
		this->help_kick(UP);
	}
	return false;
}

bool PrevPlayerScript::on_key_up(const KeyReleaseEvent & ev) {
	if (ev.key == Keycode::SPACE) {
		const vec2 DOWN = {0, 1};
		this->help_kick(DOWN);
	}
	return false;
}

void PrevPlayerScript::help_kick(const vec2 & direction) {
	// softly "kick" the player (at start/end of flight)
	vec2 & velocity = this->rb->data.linear_velocity;
	float kick_amount = std::min(
		velocity.length() * PLAYER_HELP_KICK_SCALE, engine_gravity * PLAYER_HELP_KICK_MAX
	);
	velocity += direction * kick_amount;
}
