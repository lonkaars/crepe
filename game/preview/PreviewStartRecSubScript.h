#pragma once

#include "menus/IButtonScript.h"

#include <crepe/api/Script.h>

class PreviewStartRecSubScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent & e);
};
