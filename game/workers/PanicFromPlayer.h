#pragma once

#include <crepe/api/Script.h>

class PanicFromPlayer : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);
};
