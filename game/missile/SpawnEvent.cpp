#include "SpawnEvent.h"
#include "api/Animator.h"
#include "api/BehaviorScript.h"
#include "api/Camera.h"
#include "api/Sprite.h"
#include "api/Transform.h"

using namespace crepe;

void MissileSpawnEventHandler::init() {
	subscribe<MissileSpawnEvent>([this](const MissileSpawnEvent & ev) -> bool {
		return this->on_event(ev);
	});
}

bool MissileSpawnEventHandler::on_event(const MissileSpawnEvent & ev) {
	auto ms = this->get_components_by_name<Sprite>("missile");
	auto mt = this->get_components_by_name<Transform>("missile");
	auto mbs = this->get_components_by_name<BehaviorScript>("missile");
	auto & cam = this->get_components_by_name<Transform>("camera").front().get();

	for (int i = 0; i < mbs.size(); i += 2) {
		if (!mbs[i].get().active) {
			mbs[i].get().active = true;
			mbs[i + 1].get().active = true;
			mt[i / 2].get().position.x = cam.position.x + this->MISSILE_OFFSET;
			break;
		}
	}

	return false;
}
