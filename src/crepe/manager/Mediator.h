#pragma once

#include "../util/OptionalRef.h"

// TODO: remove these singletons:
#include "EventManager.h"

namespace crepe {

class ComponentManager;
class SceneManager;
class SaveManager;
class ResourceManager;
class SDLContext;
class LoopTimer;
class ReplayManager;
class LoopManager;

/**
 * Struct to pass references to classes that would otherwise need to be singletons down to
 * other classes within the engine hierarchy. Made to prevent constant changes to subclasses to
 * pass specific references through dependency injection. All references on this struct
 * *should* be explicitly checked for availability as this struct does not guarantee anything.
 *
 * \note Dereferencing members of this struct should be deferred. If you are a user of this
 * class, keep a reference to this mediator instead of just picking references from it when you
 * receive an instance.
 *
 * \warning This class should never be directly accessible from the API
 */
struct Mediator {
	OptionalRef<SDLContext> sdl_context;
	OptionalRef<ComponentManager> component_manager;
	OptionalRef<SceneManager> scene_manager;
	OptionalRef<SaveManager> save_manager;
	OptionalRef<EventManager> event_manager = EventManager::get_instance();
	OptionalRef<ResourceManager> resource_manager;
	OptionalRef<LoopTimer> timer;
	OptionalRef<ReplayManager> replay_manager;
	OptionalRef<LoopManager> loop_manager;
};

} // namespace crepe
