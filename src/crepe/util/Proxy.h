#pragma once

#include "ValueBroker.h"

namespace crepe::util {

template <typename T>
class Proxy {
public:
	Proxy & operator = (const T &);
	operator const T & () const;

public:
	Proxy(ValueBroker<T>);

private:
	ValueBroker<T> broker;
};

}

#include "Proxy.hpp"

