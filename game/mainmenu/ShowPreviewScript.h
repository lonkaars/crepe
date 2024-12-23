#pragma once

#include "ShowScript.h"

class ShowPreviewScript : public ShowScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent& e);
	bool on_button_enter(const crepe::ButtonEnterEvent& e);
	bool on_button_exit(const crepe::ButtonExitEvent& e);
	const char* get_scene_name() const override;
};
