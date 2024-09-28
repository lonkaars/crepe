#include "crepe/SoundSystem.h"

#include <chrono>
#include <thread>

using namespace crepe;
using namespace std;
using namespace std::chrono_literals;

int main() {
	auto bgm = SoundSystem::sound("../mwe/audio/bgm.ogg");
	auto sfx1 = SoundSystem::sound("../mwe/audio/sfx1.wav");
	auto sfx2 = SoundSystem::sound("../mwe/audio/sfx2.wav");
	auto sfx3 = SoundSystem::sound("../mwe/audio/sfx3.wav");

	bgm->play();

	// play each sample sequentially
	this_thread::sleep_for(500ms);
	sfx1->play();
	this_thread::sleep_for(500ms);
	sfx2->play();
	bgm->pause();
	this_thread::sleep_for(500ms);
	sfx3->play();
	bgm->play();
	this_thread::sleep_for(500ms);

	// play all samples simultaniously
	sfx1->play();
	sfx2->play();
	sfx3->play();
	this_thread::sleep_for(1000ms);

	return 0;
}

