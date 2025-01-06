#pragma once

#include "IButtonScript.h"
#include <crepe/api/Script.h>

class ButtonSetMainMenuScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent& e);
private:
	float velocity = 20;
protected:
	bool transition = false;
};
