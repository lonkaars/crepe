#pragma once

#include "menus/IButtonScript.h"

#include <crepe/api/Script.h>

struct StartPreviewRecording : public crepe::Event {};
struct StopPreviewRecording : public crepe::Event {};

class PreviewReplaySubScript : public IButtonScript {
public:
	void init() override;
	bool on_button_press(const crepe::ButtonPressEvent & e);

private:
	crepe::recording_t recording = 0;
	bool start_recording();
	bool stop_recording();
	bool delete_recording();

private:
	bool record_saved = false;
	bool record_started = false;
};
