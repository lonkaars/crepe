#pragma once

#include <stdexcept>

#include "OptionalRef.h"

namespace crepe {

template <typename T>
OptionalRef<T>::OptionalRef(T & ref) {
	this->set(ref);
}

template <typename T>
T & OptionalRef<T>::get() const {
	if (this->ref == nullptr)
		throw std::runtime_error("OptionalRef: attempt to dereference nullptr");
	return *this->ref;
}

template <typename T>
void OptionalRef<T>::set(T & ref) noexcept {
	this->ref = &ref;
}

template <typename T>
void OptionalRef<T>::clear() noexcept {
	this->ref = nullptr;
}

template <typename T>
OptionalRef<T> & OptionalRef<T>::operator=(T & ref) {
	this->set(ref);
	return *this;
}

template <typename T>
OptionalRef<T>::operator bool() const noexcept {
	return this->ref != nullptr;
}

} // namespace crepe
