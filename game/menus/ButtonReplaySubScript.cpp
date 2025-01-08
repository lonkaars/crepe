#include "ButtonReplaySubScript.h"
#include "MenusConfig.h"

#include "../Events.h"
#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void ButtonReplaySubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
	this->subscribe<EndGameEvent>([this](const EndGameEvent & e) {
		return this->set_recording();
	});
	this->subscribe<DeleteRecordingEvent>([this](const DeleteRecordingEvent & e) {
		return this->delete_recording();
	});
	replay.record_start();
}

bool ButtonReplaySubScript::on_button_press(const ButtonPressEvent & e) {
	replay.play(this->recording);
	return false;
}

bool ButtonReplaySubScript::set_recording() {
	this->recording = replay.record_end();
	return false;
}

bool ButtonReplaySubScript::delete_recording() {
	replay.release(this->recording);
	return false;
}
