#include "PreviewStopRecSubScript.h"
#include "PreviewReplaySubScript.h"

#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PreviewStopRecSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool PreviewStopRecSubScript::on_button_press(const ButtonPressEvent & e) {
	this->trigger_event<StopPreviewRecording>();
	return false;
}
