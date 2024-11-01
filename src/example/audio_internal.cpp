/** \file
 * 
 * Standalone example for usage of the internal \c Sound class.
 */

#include <crepe/Sound.h>
#include <crepe/util/log.h>
#include <crepe/api/Config.h>

#include <thread>

using namespace crepe;
using namespace crepe::api;
using namespace std;
using namespace std::chrono_literals;
using std::make_unique;

// Unrelated stuff that is not part of this POC
int _ = [] () {
	// Show dbg_trace() output
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::LogLevel::TRACE;

	return 0; // satisfy compiler
}();



int main() {
	// Load a background track (Ogg Vorbis)
	auto bgm = Sound("../mwe/audio/bgm.ogg");
	// Load three short samples (WAV)
	auto sfx1 = Sound("../mwe/audio/sfx1.wav");
	auto sfx2 = Sound("../mwe/audio/sfx2.wav");
	auto sfx3 = Sound("../mwe/audio/sfx3.wav");

	// Start the background track
	bgm.play();

	// Play each sample sequentially while pausing and resuming the background
	// track
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
