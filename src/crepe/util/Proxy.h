#pragma once

#include "ValueBroker.h"

namespace crepe {

/**
 * \brief Utility wrapper for \c ValueBroker
 *
 * This class can be used to to wrap a ValueBroker instance so it behaves like
 * a regular variable.
 *
 * \tparam T  Type of the underlying variable
 */
template <typename T>
class Proxy {
public:
	//! Set operator
	Proxy & operator=(const T &);
	//! Get operator
	operator const T &();

public:
	Proxy(ValueBroker<T>);

private:
	ValueBroker<T> broker;
};

} // namespace crepe

#include "Proxy.hpp"
