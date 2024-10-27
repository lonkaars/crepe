#pragma once

#include <functional>

namespace crepe {

template <typename T>
class ValueBroker {
public:
	virtual void set(const T &);
	virtual const T & get();

	typedef std::function<void(T & value, const T & target)> setter_t;
	typedef std::function<const T & (T & value)> getter_t;
private:
	T & value;
	setter_t setter;
	getter_t getter;
public:
	ValueBroker(T &, const setter_t &, const getter_t &);
	ValueBroker(T &);
};

}

#include "ValueBroker.hpp"

