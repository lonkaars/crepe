#include "NpcScript.h"

#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/SaveManager.h>

using namespace std;
using namespace crepe;

void NpcScript::fixed_update(duration_t dt) {
	auto & rb = this->get_component<Rigidbody>();
	auto & npc = this->get_component<Sprite>();
	auto & transform = this->get_component<Transform>();

	if (transform.position.x < 200) {
		rb.data.linear_velocity.x *= -1;
	}
	if (transform.position.x > 700) {
		rb.data.linear_velocity.x *= -1;
	}

	if (rb.data.linear_velocity.x < 0) {
		npc.data.flip = {true, false};
	} else {
		npc.data.flip = {false, false};
	}
}
