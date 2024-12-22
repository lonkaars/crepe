#pragma once

#include <segvcatch.h>

namespace crepe {

class SignalCatch {
public:
	SignalCatch();
	~SignalCatch();

private:
	static void segv();
	static void fpe();

public:
	SignalCatch(const SignalCatch &) = delete;
	SignalCatch(SignalCatch &&) = delete;
	SignalCatch & operator=(const SignalCatch &) = delete;
	SignalCatch & operator=(SignalCatch &&) = delete;
};

}

