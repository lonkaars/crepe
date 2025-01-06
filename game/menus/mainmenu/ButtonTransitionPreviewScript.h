#pragma once

#include "ITransitionScript.h"

#include "../IButtonScript.h"

class ButtonTransitionPreviewScript : public ITransitionScript, public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent& e);
	const char* get_scene_name() const override;
};
