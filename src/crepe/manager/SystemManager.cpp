#include "../system/AISystem.h"
#include "../system/AnimatorSystem.h"
#include "../system/AudioSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/InputSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"
#include "../system/EventSystem.h"

#include "SystemManager.h"

using namespace crepe;
using namespace std;

SystemManager::SystemManager(Mediator & mediator) : Manager(mediator) {
	this->load_system<ScriptSystem>();
	this->load_system<AISystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<AnimatorSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<RenderSystem>();
	this->load_system<InputSystem>();
	this->load_system<EventSystem>();
	this->load_system<AudioSystem>();

	this->mediator.system_manager = *this;
}

void SystemManager::fixed_update() {
	for (auto & [type, system] : this->systems) {
		if (!system->active) continue;
		system->fixed_update();
	}
}

void SystemManager::frame_update() {
	for (auto & [type, system] : this->systems) {
		if (!system->active) continue;
		system->frame_update();
	}
}

