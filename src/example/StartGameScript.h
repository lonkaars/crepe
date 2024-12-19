#pragma once

#include <crepe/api/Script.h>

class StartGameScript : public crepe::Script {
public:
	void update();

private:
	bool created_hole = false;
	bool took_jetpack = false;
};
