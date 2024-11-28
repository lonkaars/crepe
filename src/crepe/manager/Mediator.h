#pragma once

#include "../util/OptionalRef.h"

// TODO: remove these singletons:
#include "SaveManager.h"
#include "EventManager.h"

namespace crepe {

class ComponentManager;
class SceneManager;

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
	OptionalRef<SaveManager> save_manager = SaveManager::get_instance();
	OptionalRef<EventManager> event_manager = EventManager::get_instance();
};

}
