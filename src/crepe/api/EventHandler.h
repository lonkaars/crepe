#pragma once

#include <functional>
#include <string>

#include "Event.h"

namespace crepe {
/**
 * \brief A type alias for an event handler function.
 * 
 * The EventHandler is a std::function that takes an EventType reference and returns a boolean value 
 * indicating whether the event is handled.
 * 
 * \tparam EventType The type of event this handler will handle.
 * 
 * Returning \c false from an event handler results in the event being propogated to other listeners for the same event type, while returning \c true stops propogation altogether.
 */
template <typename EventType>
using EventHandler = std::function<bool(const EventType & e)>;

/**
 * \class IEventHandlerWrapper
 * \brief An abstract base class for event handler wrappers.
 * 
 * This class provides the interface for handling events. Derived classes must implement the
 * `call()` method to process events and the `get_type()` method to return the handler's type.
 */
class IEventHandlerWrapper {
public:
	/**
     * \brief Virtual destructor for IEventHandlerWrapper.
     */
	virtual ~IEventHandlerWrapper() = default;

	/**
     * \brief Executes the handler with the given event.
     * 
     * This method calls the `call()` method of the derived class, passing the event to the handler.
     * 
     * \param e The event to be processed.
     * \return A boolean value indicating whether the event is handled.
     */
	bool exec(const Event & e);

	/**
     * \brief Get the type of the event handler.
     * 
     * This method returns the type of the event handler as a string.
     * 
     * \return A string representing the handler's type.
     */
	virtual std::string get_type() const = 0;

private:
	/**
     * \brief The method responsible for handling the event.
     * 
     * This method is implemented by derived classes to process the event.
     * 
     * \param e The event to be processed.
     * \return A boolean value indicating whether the event is handled.
     */
	virtual bool call(const Event & e) = 0;
};

/**
 * \class EventHandlerWrapper
 * \brief A wrapper for event handler functions.
 * 
 * This class wraps an event handler function of a specific event type. It implements the 
 * `call()` and `get_type()` methods to allow the handler to be executed and its type to be 
 * queried.
 * 
 * \tparam EventType The type of event this handler will handle.
 */
template <typename EventType>
class EventHandlerWrapper : public IEventHandlerWrapper {
public:
	/**
     * \brief Constructs an EventHandlerWrapper with a given handler.
     * 
     * The constructor takes an event handler function and stores it in the wrapper.
     * 
     * \param handler The event handler function.
     */
	explicit EventHandlerWrapper(const EventHandler<EventType> & handler);

private:
	/**
     * \brief Calls the stored event handler with the event.
     * 
     * This method casts the event to the appropriate type and calls the handler.
     * 
     * \param e The event to be handled.
     * \return A boolean value indicating whether the event is handled.
     */
	bool call(const Event & e) override;

	/**
     * \brief Returns the type of the handler.
     * 
     * This method returns a string representing the type of the event handler.
     * 
     * \return The handler type as a string.
     */
	std::string get_type() const override;

	//! The event handler function.
	EventHandler<EventType> handler;
	//! The type name of the handler function.
	const std::string handler_type;
};

} // namespace crepe

#include "EventHandler.hpp"
