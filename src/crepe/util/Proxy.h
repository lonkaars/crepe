#pragma once

#include "ValueBroker.h"

namespace crepe {

template <typename T>
class Proxy {
public:
	Proxy & operator = (const T &);
	operator const T & ();

public:
	Proxy(ValueBroker<T>);

private:
	ValueBroker<T> broker;
};

}

#include "Proxy.hpp"

