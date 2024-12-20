#pragma once

#include <crepe/api/Script.h>

class ButtonScript : public crepe::Script {
public:
	bool on_button_press(const crepe::ButtonPressEvent& e);
	bool on_button_enter(const crepe::ButtonEnterEvent& e);
	bool on_button_exit(const crepe::ButtonExitEvent& e);
	void init();
};
