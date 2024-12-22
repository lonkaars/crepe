#include "../system/AISystem.h"
#include "../system/AnimatorSystem.h"
#include "../system/AudioSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/EventSystem.h"
#include "../system/InputSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ReplaySystem.h"
#include "../system/ScriptSystem.h"

#include "SystemManager.h"

using namespace crepe;
using namespace std;

SystemManager::SystemManager(Mediator & mediator) : Manager(mediator) {
	this->load_system<InputSystem>();
	this->load_system<EventSystem>();
	this->load_system<ScriptSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<AISystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<AudioSystem>();
	this->load_system<AnimatorSystem>();
	this->load_system<RenderSystem>();
	this->load_system<ReplaySystem>();

	this->mediator.system_manager = *this;
}

void SystemManager::fixed_update() noexcept {
	for (SystemEntry & entry : this->system_order) {
		if (!entry.system.active) continue;
		try {
			entry.system.fixed_update();
		} catch (const exception & e) {
			Log::logf(
				Log::Level::WARNING, "Uncaught exception in {} fixed update: {}", entry.name,
				e.what()
			);
		}
	}
}

void SystemManager::frame_update() noexcept {
	for (SystemEntry & entry : this->system_order) {
		if (!entry.system.active) continue;
		try {
			entry.system.frame_update();
		} catch (const exception & e) {
			Log::logf(
				Log::Level::WARNING, "Uncaught exception in {} frame update: {}", entry.name,
				e.what()
			);
		}
	}
}

SystemManager::Snapshot SystemManager::save() {
	Snapshot snapshot;
	for (auto & [type, system] : this->systems) {
		snapshot[type] = system->active;
	}
	return snapshot;
}

void SystemManager::restore(const Snapshot & snapshot) {
	for (auto & [type, active] : snapshot) {
		this->systems[type]->active = active;
	}
}

void SystemManager::disable_all() {
	for (auto & [type, system] : this->systems) {
		system->active = false;
	}
}
