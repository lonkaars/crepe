#include "EndGameScript.h"

#include <crepe/api/Rigidbody.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void EndGameScript::init() {
	Rigidbody & rb_player = this->get_components_by_name<Rigidbody>("player").front();
	Rigidbody & rb_camera = this->get_components_by_name<Rigidbody>("camera").front();

	rb_player.data.linear_velocity_coefficient = vec2(0.8, 0.8);
	rb_camera.data.linear_velocity_coefficient = vec2(0.8, 0.8);
}

void EndGameScript::fixed_update(crepe::duration_t dt) {
	//logf("EndGameScript::fixed_update");
	// ...
}
