#include <crepe/api/Rigidbody.h>
#include <cassert>

#include "PlayerScript.h"

using namespace crepe;
using namespace std;

PlayerScript::PlayerScript(const PlayerObject & player) : player(player) { }

void PlayerScript::fixed_update(crepe::duration_t dt) {
	if (this->get_key_state(Keycode::SPACE))
		player.body.add_force_linear({ 0, -10 });
}

