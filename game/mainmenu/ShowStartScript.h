#pragma once

#include "IShowScript.h"

class ShowStartScript : public IShowScript {
public:
	void init() override;
	void fixed_update(crepe::duration_t dt) override;
	const char* get_scene_name() const override;
};
