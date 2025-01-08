#pragma once

#include "ITransitionScript.h"

class TransitionStartSubScript : public ITransitionScript {
public:
	void fixed_update(crepe::duration_t dt) override;
	const char * get_scene_name() const override;
};
