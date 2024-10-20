#pragma once

#include <cstdlib> // For malloc and free
#include <new> // For placement new
#include <stdexcept> // For std::bad_alloc
#include <utility> // For std::move and std::forward
#include <vector> // For returning references

template <typename T>
class ContiguousContainer {
public:
	ContiguousContainer();
	~ContiguousContainer();

	// Use perfect forwarding for pushBack
	template <typename... Args>
	void pushBack(Args &&... args);

	void popBack();
	T & operator[](size_t index);
	size_t getSize() const;

	// Function to return references to all stored objects
	std::vector<std::reference_wrapper<T>> getAllReferences();

private:
	T * mData;
	size_t mSize;
	size_t mCapacity;

	void resize(size_t new_capacity); // Resize function to allocate more space
};

#include "ContiguousContainer.hpp"
