#include "SpawnEvent.h"

#include <crepe/api/AudioSource.h>
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

bool MissileSpawnEventHandler::on_event(const MissileSpawnEvent & event) {
    auto missile_sprites = this->get_components_by_name<Sprite>("missile");
    auto missile_transforms = this->get_components_by_name<Transform>("missile");
    auto missile_behaviorscripts = this->get_components_by_name<BehaviorScript>("missile");
    auto missile_audiosources = this->get_components_by_name<AudioSource>("missile");
    auto & camera_transform = this->get_components_by_name<Transform>("camera").front().get();

    for (size_t i = 0; i < missile_behaviorscripts.size(); ++i) {
        auto & script = missile_behaviorscripts[i].get();
        if (!script.active) {
            script.active = true;

            missile_audiosources[i * 2].get().play(true);

            auto & transform = missile_transforms[i].get();
            transform.position.x = camera_transform.position.x + this->MISSILE_OFFSET;

            std::uniform_int_distribution<> dist(this->MIN_RANGE, this->MAX_RANGE);
            transform.position.y = dist(gen);

            break;
        }
    }

    return false;
}
