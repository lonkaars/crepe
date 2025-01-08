#pragma once



#include "api/Script.h"
#include <functional>
#include <vector>


class ObjectsScheduler : public crepe::Script {

private:
	std::vector<std::function<void()>> obstacles;
	
	int last_boss_check = 0;
	int last_obstacle_check = 0;

	int boss_fight_interval = 1000;
	int obstacle_interval = 3000;
	int start_offset = 1300;

private:
	void preset_0();
	void preset_1();
	void preset_2();
	void preset_3();
	void preset_4();
	void boss_fight_1();

	bool boss_fight_1_event();

public:
	void init();
	void fixed_update(crepe::duration_t dt);

};
