#pragma once

#include <crepe/api/Script.h>
#include <crepe/manager/SaveManager.h>

class SpeedScript : public crepe::Script {
public:
	void init() override;
	void fixed_update(crepe::duration_t dt) override;

private:
	crepe::SaveManager * savemgr;
	bool toggle = true;
	float timescale = 1;
};
