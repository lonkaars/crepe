#include "PreviewReplaySubScript.h"
#include "Config.h"
#include "menus/ButtonReplaySubScript.h"
#include <crepe/api/AudioSource.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PreviewReplaySubScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
	this->subscribe<StopPreviewRecording>([this](const StopPreviewRecording & e) {
		return this->stop_recording();
	});
	this->subscribe<DeleteRecordingEvent>([this](const DeleteRecordingEvent & e) {
		return this->delete_recording();
	});
	this->subscribe<StartPreviewRecording>([this](const StartPreviewRecording & e) {
		return this->start_recording();
	});
	
}

bool PreviewReplaySubScript::on_button_press(const ButtonPressEvent & e) {
	if(DISABLE_REPLAY)return false;
	replay.play(this->recording);
	return false;
}
bool PreviewReplaySubScript::start_recording(){
	if(DISABLE_REPLAY)return false;
	if(record_saved){
		this->stop_recording();
		this->delete_recording();
	}
	replay.record_start();
	this->record_started = true;
	return false;
}

bool PreviewReplaySubScript::stop_recording() {
	if(DISABLE_REPLAY)return false;
	if(this->record_started)this->recording = replay.record_end();
	this->record_saved = true;
	return false;
}

bool PreviewReplaySubScript::delete_recording() {
	if(DISABLE_REPLAY)return false;
	if(this->record_started) this->stop_recording();
	if(this->record_saved)replay.release(this->recording);
	this->record_saved = false;
	return false;
}
