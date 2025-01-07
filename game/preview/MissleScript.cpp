#include "MissleScript.h"
#include "types.h"

#include <cmath>
#include <crepe/api/AI.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Sprite.h>

using namespace std;
using namespace crepe;

/*
bool MissleScript::mouse_click(const MouseClickEvent & ev) {
	this->mouse_pos = ev.mouse_pos;
	this->get_component<Transform>().position = mouse_pos;
	return true;
}

*/
void MissleScript::init() {
	/*
	subscribe<MouseClickEvent>([this](const MouseClickEvent & ev) -> bool {
		return this->mouse_click(ev);
	});
	*/
}

void MissleScript::fixed_update(crepe::duration_t dt) {
	const auto & player = this->get_components_by_name<Transform>("player").front().get();
	const auto & rb = this->get_component<Rigidbody>();

	auto & missile = this->get_component<Transform>();
	auto & m_ai = this->get_component<AI>();

	m_ai.seek_target = player.position;
	m_ai.seek_on();

	vec2 angle_pos = rb.data.linear_velocity;
	float angle = atan2(angle_pos.y, angle_pos.x) * (180 / M_PI);

	missile.rotation = angle;
}
