#pragma once

#include "IButtonScript.h"

#include <crepe/api/Script.h>

class ButtonReplaySubScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent & e);
private:
	crepe::recording_t recording = 0;
	bool set_recording();

protected:
	bool transition = false;
};
