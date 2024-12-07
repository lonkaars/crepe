#pragma once

#include <vector>

#include "../ValueBroker.h"
#include "../manager/EventManager.h"
#include "../manager/Mediator.h"
#include "../system/CollisionSystem.h"
#include "../types.h"
#include "../util/OptionalRef.h"

namespace crepe {

class ScriptSystem;
class BehaviorScript;
class ComponentManager;

/**
 * \brief Script interface
 *
 * This class is used as a base class for user-defined scripts that can be added to game
 * objects using the \c BehaviorScript component.
 *
 * \note Additional *events* (like Unity's OnDisable and OnEnable) should be implemented as
 * member or lambda methods in derivative user script classes and registered in \c init().
 *
 * \warning Concrete scripts are allowed do create a custom constructor, but the utility
 * functions should not be called inside the constructor as they rely on late references that
 * are only available after the constructor returns.
 *
 * \see feature_script
 */
class Script {
protected:
	/**
	 * \name Interface functions
	 * \{
	 */
	/**
	 * \brief Script initialization function (empty by default)
	 *
	 * This function is called during the ScriptSystem::update() routine *before*
	 * Script::update() if it (a) has not yet been called and (b) the \c BehaviorScript component
	 * holding this script instance is active.
	 */
	virtual void init() {}
	/**
	 * \brief Script update function (empty by default)
	 *
	 * This function is called during the ScriptSystem::update() routine if the \c BehaviorScript
	 * component holding this script instance is active.
	 */
	virtual void update() {}
	//! \}

	//! ScriptSystem calls \c init() and \c update()
	friend class crepe::ScriptSystem;

protected:
	/**
	 * \name Utility functions
	 * \{
	 */

	/**
	 * \brief Get single component of type \c T on this game object
	 *
	 * \tparam T Type of component
	 *
	 * \returns Reference to component
	 *
	 * \throws std::runtime_error if this game object does not have a component with type \c T
	 */
	template <typename T>
	T & get_component() const;
	// TODO: make get_component calls for component types that can have more than 1 instance
	// cause compile-time errors

	/**
	 * \brief Get all components of type \c T on this game object
	 *
	 * \tparam T Type of component
	 *
	 * \returns List of component references
	 */
	template <typename T>
	RefVector<T> get_components() const;

	/**
	 * \brief Log a message using Log::logf
	 *
	 * \tparam Args Log::logf parameters
	 * \param args  Log::logf parameters
	 */
	template <typename... Args>
	void logf(Args &&... args);

	/**
	 * \brief Subscribe to an event with an explicit channel
	 * \see EventManager::subscribe
	 */
	template <typename EventType>
	void subscribe(const EventHandler<EventType> & callback, event_channel_t channel);
	/**
	 * \brief Subscribe to an event on EventManager::CHANNEL_ALL
	 * \see EventManager::subscribe
	 */
	template <typename EventType>
	void subscribe(const EventHandler<EventType> & callback);

	/**
	 * \brief Set the next scene using SceneManager
	 * \see SceneManager::set_next_scene
	 */
	void set_next_scene(const std::string & name);

	//! Retrieve SaveManager reference
	SaveManager & get_save_manager() const;

	//! \}

private:
	/**
	 * \brief Internal subscribe function
	 *
	 * This function exists so certain template specializations of Script::subscribe can be
	 * explicitly deleted, and does the following:
	 * - Wrap the user-provided callback in a check that tests if the parent BehaviorScript
	 *   component is still active
	 * - Store the subscriber handle returned by the event manager so this listener is
	 *   automatically unsubscribed at the end of this Script instance's life
	 *
	 * \tparam EventType concrete Event class
	 * \param callback User-provided callback function
	 * \param channel Event channel (may have been overridden by template specializations)
	 */
	template <typename EventType>
	void subscribe_internal(const EventHandler<EventType> & callback, event_channel_t channel);

protected:
	// NOTE: This must be the only constructor on Script, see "Late references" below
	Script() = default;
	//! Only \c BehaviorScript instantiates Script
	friend class BehaviorScript;

public:
	// std::unique_ptr destroys script
	virtual ~Script();

private:
	Script(const Script &) = delete;
	Script(Script &&) = delete;
	Script & operator=(const Script &) = delete;
	Script & operator=(Script &&) = delete;

private:
	/**
	 * \name Late references
	 *
	 * These references are set by BehaviorScript immediately after calling the constructor of
	 * Script.
	 *
	 * \note Script must have a constructor without arguments so the game programmer doesn't need
	 * to manually add `using Script::Script` to their concrete script class if they want to
	 * implement a non-default constructor (e.g. for passing references to their own concrete
	 * Script classes).
	 *
	 * \{
	 */
	//! Game object ID of game object parent BehaviorScript is attached to
	game_object_id_t game_object_id;
	//! Reference to parent component
	OptionalRef<bool> active;
	//! Mediator reference
	OptionalRef<Mediator> mediator;
	//! \}

private:
	//! Flag to indicate if \c init() has been called already
	bool initialized = false;
	//! List of subscribed events
	std::vector<subscription_t> listeners;
};

/**
 * \brief Subscribe to CollisionEvent for the current GameObject
 *
 * This is a template specialization for Script::subscribe which automatically sets the event
 * channel so the callback handler is only called for CollisionEvent events that apply to the
 * current GameObject the parent BehaviorScript is attached to.
 */
template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback);
template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback, event_channel_t)
	= delete;

} // namespace crepe

#include "Script.hpp"
