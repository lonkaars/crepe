#pragma once

#include <crepe/api/Script.h>

class PlayerEndScript : public crepe::Script {
public:
	void init();
	void fixed_update(crepe::duration_t dt);

private:
	int jump = 0;
};
