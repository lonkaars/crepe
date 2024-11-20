#pragma once

#include "Proxy.h"

namespace crepe {

template <typename T>
Proxy<T>::Proxy(ValueBroker<T> broker) : broker(broker) {}

template <typename T>
Proxy<T> & Proxy<T>::operator=(const T & val) {
	this->broker.set(val);
	return *this;
}

template <typename T>
Proxy<T> & Proxy<T>::operator=(Proxy & proxy) {
	this->broker.set(T(proxy));
	return *this;
}

template <typename T>
Proxy<T>::operator const T &() {
	return this->broker.get();
}

} // namespace crepe
