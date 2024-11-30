#pragma once

#include <functional>
#include <typeindex>

namespace crepe {

class Private {
public:
	Private() = default;
	~Private();
	Private(const Private &);
	Private(Private &&);
	Private & operator=(const Private &);
	Private & operator=(Private &&);

	template <typename T>
	T & get();

	template <typename T, typename... Args>
	T & set(Args &&... args);

	bool empty() const noexcept;

private:
	std::function<void(void *)> destructor;
	std::type_index type = typeid(void);
	void * instance = nullptr;
};

} // namespace crepe

#include "Private.hpp"
