#pragma once

#include <typeindex>
#include <functional>

namespace crepe {

class Private {
public:
	Private() = default;
	~Private();
	Private(Private &&);
	Private & operator=(Private &&);
	Private(const Private &) = delete;
	Private & operator=(const Private &) = delete;

	template <typename T>
	T & get();

	template <typename T, typename... Args>
	void set(Args &&... args);

	bool empty() const noexcept;

private:
	std::function<void(void *)> destructor;
	std::type_index type = typeid(void);
	void * instance = nullptr;
};

}

#include "Private.hpp"

