#pragma once

#include "../IButtonScript.h"

#include <crepe/api/Script.h>

class ButtonBuySelectBulletScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent & e);

protected:
	bool transition = false;
};
