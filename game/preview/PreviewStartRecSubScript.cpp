#include "PreviewStartRecSubScript.h"
#include "PreviewReplaySubScript.h"

#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PreviewStartRecSubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool PreviewStartRecSubScript::on_button_press(const ButtonPressEvent & e) {
	this->trigger_event<StartPreviewRecording>();
	return false;
}
