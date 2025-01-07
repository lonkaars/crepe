#include "SpawnEvent.h"
#include "api/AI.h"
#include "api/AudioSource.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>

#include <cstdlib>
#include <random>

using namespace crepe;

void MissileSpawnEventHandler::init() {
	subscribe<MissileSpawnEvent>([this](const MissileSpawnEvent & ev) -> bool {
		return this->on_event(ev);
	});

}

std::random_device rd;
std::mt19937 gen(rd());

bool MissileSpawnEventHandler::on_event(const MissileSpawnEvent & ev) {
	auto ms = this->get_components_by_name<Sprite>("missile");
	auto mt = this->get_components_by_name<Transform>("missile");
	auto mbs = this->get_components_by_name<BehaviorScript>("missile");
	auto mas = this->get_components_by_name<AudioSource>("missile");
	auto & cam = this->get_components_by_name<Transform>("camera").front().get();

	for (int i = 0; i < mbs.size(); i++) {
		if (!mbs[i].get().active) {
			mbs[i].get().active = true;

			mas[i*2].get().active = true;
			mas[i*2].get().play(true);

			mt[i].get().position.x = cam.position.x + this->MISSILE_OFFSET;
			std::uniform_int_distribution<> dist(this->MIN_RANGE,this->MAX_RANGE);
			mt[i].get().position.y = dist(gen);
			break;
		}
	}

	return false;
}
