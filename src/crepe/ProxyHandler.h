#pragma once

namespace crepe {

template <typename T>
class ProxyHandler {
public:
	virtual void set(const T &) = 0;
	virtual const T & get() = 0;
};

}

