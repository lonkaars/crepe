#include "AlertScript.h"
#include "../Config.h"
#include "api/CircleCollider.h"
#include "api/Sprite.h"

#include <crepe/api/Transform.h>

using namespace crepe;

void AlertScript::fixed_update(crepe::duration_t dt) {
	const auto & cam = this->get_components_by_name<Transform>("camera").front().get();
	//missile transform
	const auto & this_transform = this->get_component<Transform>();
	auto missile_transforms = this->get_components_by_name<Transform>("missile");
	const auto & this_collider = this->get_component<CircleCollider>();

	auto alert_sprites = this->get_components_by_name<Sprite>("missile_alert");
	auto alert_transforms = this->get_components_by_name<Transform>("missile_alert");

	int idx = 0;
	for (int i = 0; i < missile_transforms.size(); i++) {
		const auto & missile_transform = missile_transforms[i].get();
		if (this_transform.game_object_id == missile_transform.game_object_id) {
			idx = i;
			break;
		}
	}

	auto & alert_transform = alert_transforms[idx].get();
	alert_transform.position.x = cam.position.x + (VIEWPORT_X / 2 - 100);
	alert_transform.position.y = this_transform.position.y;

	// check if transform is in camera view
	if (this_transform.position.x > cam.position.x - (VIEWPORT_X / 2)
		&& this_transform.position.x < cam.position.x + (VIEWPORT_X / 2)) {
		alert_sprites[idx].get().active = false;
	}
}
