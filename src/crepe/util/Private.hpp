#pragma once

#include <stdexcept>
#include <format>

#include "Private.h"

namespace crepe {

template <typename T, typename... Args>
void Private::set(Args &&... args) {
	T * instance = new T(std::forward<Args>(args)...);
	this->instance = static_cast<void*>(instance);
	this->destructor = [](void * instance) {
		delete static_cast<T*>(instance);
	};
	this->type = typeid(T);
}

template <typename T>
T & Private::get() {
	using namespace std;
	if (this->empty())
		throw out_of_range("Private: get() called on empty object");
	type_index requested_type = typeid(T);
	if (this->type != requested_type)
		throw logic_error(format("Private: get() called with [T = {}] (actual is [T = {}])", requested_type.name(), this->type.name()));
	return *static_cast<T*>(this->instance);
}

}
