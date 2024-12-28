#pragma once

#include "IButtonScript.h"
#include "IShowScript.h"

class ShowPreviewScript : public IShowScript, public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent& e);
	const char* get_scene_name() const override;
};
