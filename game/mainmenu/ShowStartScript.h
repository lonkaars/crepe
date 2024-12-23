#pragma once

#include "ShowScript.h"

class ShowStartScript : public ShowScript {
public:
	void init() override;
	void fixed_update(crepe::duration_t dt) override;
	const char* get_scene_name() const override;
};
