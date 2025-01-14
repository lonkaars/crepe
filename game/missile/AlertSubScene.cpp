#include "AlertSubScene.h"
#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;

MissileAlert::MissileAlert(Scene & scn) {
	GameObject alert = scn.new_object("missile_alert", "missile_alert", {0, 0}, 0, 1);

	Asset missile_alert_ss {"asset/obstacles/missile/missileAlert.png"};

	auto & missile_alert_sprite = alert.add_component<Sprite>(
		missile_alert_ss,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.size = {0, 100},
		}
	);

	auto & missile_alert_anim = alert.add_component<Animator>(
		missile_alert_sprite, ivec2 {64, 64}, uvec2 {4, 2},
		Animator::Data {
			.fps = 15,
			.looping = true,
		}
	);

	missile_alert_anim.set_anim(1);
	missile_alert_sprite.active = false;
}
