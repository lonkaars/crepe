#include "MissleScript.h"
#include "api/AI.h"
#include "api/Sprite.h"

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
	auto & m_ai = this->get_component<AI>();
	const auto & rb = this->get_component<Rigidbody>();
	auto & missle = this->get_component<Sprite>();
	m_ai.seek_target = player.position;
	m_ai.seek_on();

	if (rb.data.linear_velocity.x > 0) {
		missle.data.flip = {true, false};
	} else {
		missle.data.flip = {false, false};
	}
}
