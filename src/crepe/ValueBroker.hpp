#pragma once

#include <memory>

#include "ValueBroker.h"

namespace crepe {

template <typename T>
ValueBroker<T>::ValueBroker(T & value) :
	value(value),
	setter([] (T & value, const T & target) {
		value = std::move(target);
	}),
	getter([] (T & value) -> const int & {
		return value;
	})
	{
}

template <typename T>
ValueBroker<T>::ValueBroker(T & value, const setter_t & setter, const getter_t & getter) :
	value(value),
	setter(setter),
	getter(getter)
	{
}

template <typename T>
const T & ValueBroker<T>::get() {
	return this->getter(this->value);
}

template <typename T>
void ValueBroker<T>::set(const T & value) {
	this->setter(this->value, value);
}

}

