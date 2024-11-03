#pragma once

#include <functional>

namespace crepe {

template <typename T>
class ValueBroker {
public:
	virtual void set(const T &);
	virtual const T & get();

	typedef std::function<void(const T & target)> setter_t;
	typedef std::function<const T & ()> getter_t;
private:
	setter_t setter;
	getter_t getter;
public:
	ValueBroker(const setter_t &, const getter_t &);
	ValueBroker(T &);
};

}

#include "ValueBroker.hpp"

