#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main() {
	SoLoud::Soloud soloud;
	soloud.init();

	// load background track
	SoLoud::WavStream bgm;
	bgm.load("../bgm.ogg");
	// NOTE: SoLoud::Wav is poorly named as it also supports FLAC, MP3 and OGG

	// load three short samples
	SoLoud::Wav sfx[3];
	sfx[0].load("../sfx1.wav");
	sfx[1].load("../sfx2.wav");
	sfx[2].load("../sfx3.wav");

	// start the background track
	SoLoud::handle bgm_handle = soloud.play(bgm);

	// play each sample sequentially
	this_thread::sleep_for(500ms);
	soloud.play(sfx[0]);
	this_thread::sleep_for(500ms);
	soloud.play(sfx[1]);
	soloud.setPause(bgm_handle, true);
	this_thread::sleep_for(500ms);
	soloud.play(sfx[2]);
	soloud.setPause(bgm_handle, false);
	this_thread::sleep_for(500ms);

	// play all samples simultaniously
	for (unsigned i = 0; i < 3; i++) soloud.play(sfx[i]);
	this_thread::sleep_for(1000ms);

	// stop all audio and exit
	soloud.deinit();
	return 0;
}
