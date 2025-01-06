#pragma once

#include "api/Script.h"
#include "manager/SaveManager.h"

class HudScript : public crepe::Script {
public:
	void init() override;
	void frame_update(crepe::duration_t dt) override;
private:
	crepe::SaveManager* savemgr;
	bool show_fps = false;
};
