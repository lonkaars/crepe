#pragma once

#include "IButtonScript.h"

#include <crepe/api/Script.h>

struct DeleteRecordingEvent : public crepe::Event {};

class ButtonReplaySubScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent & e);

private:
	crepe::recording_t recording = 0;
	bool set_recording();
	bool delete_recording();

protected:
	bool transition = false;
};
