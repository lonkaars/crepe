#pragma once

#include "api/Script.h"
#include "manager/SaveManager.h"

class SpeedScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt) override;
private:
	crepe::SaveManager* savemgr;
	bool toggle = true;
	float timescale = 1;
};
