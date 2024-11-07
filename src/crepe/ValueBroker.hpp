#pragma once

#include "ValueBroker.h"

namespace crepe {

template <typename T>
ValueBroker<T>::ValueBroker(const setter_t & setter, const getter_t & getter)
	: setter(setter),
	  getter(getter) {}

template <typename T>
const T & ValueBroker<T>::get() {
	return this->getter();
}

template <typename T>
void ValueBroker<T>::set(const T & value) {
	this->setter(value);
}

} // namespace crepe
