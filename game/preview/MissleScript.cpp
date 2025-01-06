#include "MissleScript.h"
#include "types.h"

#include <cmath>
#include <crepe/api/AI.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Sprite.h>
#include <iostream>

using namespace std;
using namespace crepe;

bool MissleScript::mouse_click(const MouseClickEvent & ev) {
	this->mouse_pos = ev.mouse_pos;
	this->get_component<Transform>().position = mouse_pos;
	return true;
}

void MissleScript::init() {
	subscribe<MouseClickEvent>([this](const MouseClickEvent & ev) -> bool {
		return this->mouse_click(ev);
	});
}

void MissleScript::fixed_update(crepe::duration_t dt) {
	const auto & player = this->get_components_by_name<Transform>("player").front().get();
	const auto & missile = this->get_component<Transform>();
	auto & m_ai = this->get_component<AI>();
	const auto & rb = this->get_component<Rigidbody>();
	auto & img = this->get_component<Sprite>();
	if (this->get_key_state(Keycode::M)) {
		m_ai.seek_off();
	} else {
		m_ai.seek_target = player.position;
		m_ai.seek_on();

		vec2 angle_pos = missile.position - player.position;
		float angle = atan2(angle_pos.y, angle_pos.x) * (180 / M_PI);

		if (rb.data.linear_velocity.x > 0) {
			img.data.flip = {true, false};
			angle -= 180;
		} else {
			img.data.flip = {false, false};
		}

		img.data.angle_offset = angle;
	}
}
