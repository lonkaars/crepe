#include <crepe/api/Rigidbody.h>
#include <cassert>

#include "PlayerScript.h"

using namespace crepe;
using namespace std;

PlayerScript::PlayerScript(PlayerObject * player) : player(player) {
	logf(Log::DEBUG, "PlayerScript: [C] player         {}", (void*) &(*player));
	logf(Log::DEBUG, "PlayerScript: [C] player.body    {}", (void*) &(player->body));
	logf(Log::DEBUG, "PlayerScript: [C] player.body.id {}", (void*) &(player->body.game_object_id));
}

void PlayerScript::init() {
	logf(Log::DEBUG, "PlayerScript: [C] player         {}", (void*) &(*player));
	logf(Log::DEBUG, "PlayerScript: [C] player.body    {}", (void*) &(player->body));
	logf(Log::DEBUG, "PlayerScript: [C] player.body.id {}", (void*) &(player->body.game_object_id));
	player->controller.active = false;
}

void PlayerScript::fixed_update(crepe::duration_t dt) {
	if (this->get_key_state(Keycode::SPACE))
		player->body.add_force_linear({ 0, -10 });
}

