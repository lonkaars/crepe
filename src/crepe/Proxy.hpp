#pragma once

#include "Proxy.h"

namespace crepe {

template <typename T>
Proxy<T> & Proxy<T>::operator = (const T & val) {
	this->val->set(val);
	return *this;
}

template <typename T>
Proxy<T>::operator const T & () const {
	return this->val->get();
}

}

