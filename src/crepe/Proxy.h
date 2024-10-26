#pragma once

#include <memory>

#include "ProxyHandler.h"

namespace crepe {

template <typename T>
class Proxy {
public:
	Proxy & operator = (const T &);
	operator const T & () const;

public:
	Proxy(std::unique_ptr<ProxyHandler<T>> handler) : val(std::move(handler)) {}
private:
	std::unique_ptr<ProxyHandler<T>> val = nullptr;
};

}

#include "Proxy.hpp"
