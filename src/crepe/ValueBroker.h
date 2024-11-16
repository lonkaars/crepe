#pragma once

#include <functional>

namespace crepe {

/**
 * \brief Give reference to value through custom set/get functions
 *
 * This class can be used to abstract direct access to any arbitrary value through a custom get
 * and set function passed to its constructor. Consumers of this type may want to wrap it in a
 * \c Proxy so it behaves like a regular variable.
 *
 * \tparam T  Type of the underlying variable
 */
template <typename T>
class ValueBroker {
public:
	//! Set the value
	virtual void set(const T &);
	//! Retrieve the value
	virtual const T & get();

	typedef std::function<void(const T & target)> setter_t;
	typedef std::function<const T &()> getter_t;

private:
	setter_t setter;
	getter_t getter;

public:
	/**
	 * \param setter  Function that sets the variable
	 * \param getter  Function that retrieves the variable
	 */
	ValueBroker(const setter_t & setter, const getter_t & getter);
};

} // namespace crepe

#include "ValueBroker.hpp"
