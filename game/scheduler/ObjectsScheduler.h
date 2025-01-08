#pragma once



#include "api/Script.h"
#include <functional>
#include <vector>


class ObjectsScheduler : public crepe::Script {

private:
	std::vector<std::function<void()>> obstacles;
	
	int last_check = 0;

public:
	void init();
	void fixed_update(crepe::duration_t dt);

};
