/** \file
 * 
 * Standalone example for usage of the internal \c Sound class.
 */

#include <crepe/api/Config.h>
#include <crepe/facade/SoundContext.h>
#include <crepe/facade/Sound.h>
#include <crepe/Asset.h>
#include <crepe/util/Log.h>

#include <thread>

using namespace crepe;
using namespace std;
using namespace std::chrono_literals;
using std::make_unique;

// Unrelated stuff that is not part of this POC
int _ = []() {
	// Show dbg_trace() output
	auto & cfg = Config::get_instance();
	cfg.log.level = Log::Level::TRACE;

	return 0; // satisfy compiler
}();

int main() {
	SoundContext ctx{};
	Sound sound{ctx};
	// Load a background track (Ogg Vorbis)
	auto _bgm = sound.clone(Asset{"mwe/audio/bgm.ogg"});
	Sound & bgm = *dynamic_cast<Sound *>(_bgm.get());
	// Load three short samples (WAV)
	auto _sfx1 = sound.clone(Asset{"mwe/audio/sfx1.wav"});
	Sound & sfx1 = *dynamic_cast<Sound *>(_sfx1.get());
	auto _sfx2 = sound.clone(Asset{"mwe/audio/sfx2.wav"});
	Sound & sfx2 = *dynamic_cast<Sound *>(_sfx2.get());
	auto _sfx3 = sound.clone(Asset{"mwe/audio/sfx3.wav"});
	Sound & sfx3 = *dynamic_cast<Sound *>(_sfx3.get());

	// Start the background track
	bgm.play();

	// Play each sample sequentially while pausing and resuming the background track
	this_thread::sleep_for(500ms);
	sfx1.play();
	this_thread::sleep_for(500ms);
	sfx2.play();
	bgm.pause();
	this_thread::sleep_for(500ms);
	sfx3.play();
	bgm.play();
	this_thread::sleep_for(500ms);

	// Play all samples simultaniously
	sfx1.play();
	sfx2.play();
	sfx3.play();
	this_thread::sleep_for(1000ms);

	// Stop all audio and exit
	return EXIT_SUCCESS;
}
