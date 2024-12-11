#pragma once

#include "../util/OptionalRef.h"

// TODO: remove these singletons:
#include "../facade/SDLContext.h"

#include "SaveManager.h"

namespace crepe {

class ComponentManager;
class SceneManager;
class SaveManager;
class ResourceManager;

class LoopTimerManager;
class EventManager;
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
	OptionalRef<ComponentManager> component_manager;
	OptionalRef<SceneManager> scene_manager;
	OptionalRef<EventManager> event_manager;
	OptionalRef<LoopTimerManager> loop_timer;
	OptionalRef<SaveManager> save_manager;
	OptionalRef<ResourceManager> resource_manager;
	OptionalRef<SDLContext> sdl_context = SDLContext::get_instance();
};

} // namespace crepe
