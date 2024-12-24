#include "PlayerScript.h"

#include <crepe/api/Rigidbody.h>

using namespace crepe;
using namespace std;

void PlayerScript::fixed_update(crepe::duration_t dt) {
	Rigidbody & rb = this->get_components_by_name<Rigidbody>("player").front();
	if (this->get_key_state(Keycode::SPACE)) rb.add_force_linear(vec2(0, -10));
}
