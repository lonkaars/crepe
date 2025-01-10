#include "SpawnEvent.h"
#include "Random.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>

#include <cstdlib>

using namespace crepe;

void MissileSpawnEventHandler::init() {
	subscribe<MissileSpawnEvent>([this](const MissileSpawnEvent & ev) -> bool {
		return this->on_event(ev);
	});
}

bool MissileSpawnEventHandler::on_event(const MissileSpawnEvent & event) {
	auto missile_transforms = this->get_components_by_name<Transform>("missile");
	auto alert_sprites = this->get_components_by_name<Sprite>("missile_alert");
	auto alert_transforms = this->get_components_by_name<Transform>("missile_alert");
	auto colliders = this->get_components_by_name<CircleCollider>("missile");
	auto missile_behaviorscripts = this->get_components_by_name<BehaviorScript>("missile");
	auto missile_audiosources = this->get_components_by_name<AudioSource>("missile");
	auto & camera_transform = this->get_components_by_name<Transform>("camera").front().get();

	for (size_t i = 0; i < missile_behaviorscripts.size(); ++i) {
		auto & script = missile_behaviorscripts[i * 2].get();
		if (script.active) continue;
		script.active = true;
		colliders[i].get().active = true;
		missile_audiosources[i * 2].get().play();

		auto & transform = missile_transforms[i].get();
		transform.position.x = camera_transform.position.x + this->MISSILE_OFFSET;
		transform.position.y = Random::i(this->MAX_RANGE, this->MIN_RANGE);

		auto & alert_transform = alert_transforms[i].get();
		auto & alert_sprite = alert_sprites[i].get();
		alert_sprite.active = true;
		break;
	}

	return false;
}
