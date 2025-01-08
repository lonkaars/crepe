#include "AquariumScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void AquariumScript::fixed_update(crepe::duration_t dt) {
	Transform & trans_cam = this->get_components_by_name<Transform>("camera").front();

	float cam_left_x = trans_cam.position.x - VIEWPORT_X / 2;

	if (cam_left_x > this->start_x + this->lenght) {
		//Move whole background 12000 to the right
		RefVector<Transform> trans = this->get_components_by_tag<Transform>("background_aqua");
		for (Transform & tran : trans) {
			tran.position.x += 12000;
		}
		this->start_x += 12000;
	}
}
