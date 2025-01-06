#include "PlayerScript.h"

#include <crepe/api/AudioSource.h>
#include <crepe/api/Camera.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;

bool PlayerScript::key_pressed(const KeyPressEvent & ev) {
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

		case Keycode::SPACE:
			this->get_component<Rigidbody>().data.linear_velocity.y = -move_speed;
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
			this->head->data.angle_offset -= 1;
			break;
		case Keycode::RIGHT:
			this->head->data.angle_offset += 1;
			break;
		case Keycode::UP:
			this->head->data.scale_offset += 0.1;
			break;
		case Keycode::DOWN:
			this->head->data.scale_offset -= 0.1;
			break;
		case Keycode::P:
			this->get_component<AudioSource>().play();
			break;
		case Keycode::Q:
			this->get_components_by_name<Camera>("camera").front().get().data.zoom -= 0.01;
			break;
		case Keycode::E:
			this->get_components_by_name<Camera>("camera").front().get().data.zoom += 0.01;
			break;
		case Keycode::J:
			this->get_components_by_name<Camera>("camera").front().get().data.postion_offset.x
				-= move_speed;
			break;
		case Keycode::K:
			this->get_components_by_name<Camera>("camera").front().get().data.postion_offset.y
				-= move_speed;
			break;
		case Keycode::L:
			this->get_components_by_name<Camera>("camera").front().get().data.postion_offset.x
				+= move_speed;
			break;
		case Keycode::I:
			this->get_components_by_name<Camera>("camera").front().get().data.postion_offset.y
				+= move_speed;
			break;
			//todo
		case Keycode::PAGE_UP:
		case Keycode::PAGE_DOWN:
		case Keycode::HOME:
			break;
		default:
			break;
	}
	return false;
}

void PlayerScript::init() {
	auto animations = this->get_components<Animator>();
	body_anim = animations[0];
	head_anim = animations[1];

	auto sprites = this->get_components<Sprite>();
	body = sprites[0];
	head = sprites[1];

	subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		return this->key_pressed(ev);
	});
};

void PlayerScript::fixed_update(crepe::duration_t dt) {
	auto & savemgr = this->get_save_manager();
	const auto & pos = this->get_component<Transform>().position;

	savemgr.set("player_x", pos.x);
	savemgr.set("player_y", pos.y);
};
