#include <miniaudio.h>

#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main() {
	ma_engine engine;
	ma_engine_init(NULL, &engine);

	// 1. load background track (ogg vorbis)
	ma_sound bgm;
	ma_sound_init_from_file(&engine, "../bgm.ogg", 0, NULL, NULL, &bgm);

	// 2. load samples (wav)
	ma_sound sfx[3];
	ma_sound_init_from_file(&engine, "../sfx1.wav", 0, NULL, NULL, &sfx[0]);
	ma_sound_init_from_file(&engine, "../sfx2.wav", 0, NULL, NULL, &sfx[1]);
	ma_sound_init_from_file(&engine, "../sfx3.wav", 0, NULL, NULL, &sfx[2]);

	// 3. start the background track
	ma_sound_start(&bgm);

	// 4. play samples sequentially while controlling the background track
	this_thread::sleep_for(500ms);
	ma_sound_start(&sfx[0]);
	this_thread::sleep_for(500ms);
	ma_sound_start(&sfx[1]);
	ma_sound_stop(&bgm);
	this_thread::sleep_for(500ms);
	ma_sound_start(&sfx[2]);
	ma_sound_start(&bgm); // this actually resumes now
	this_thread::sleep_for(500ms);
	for (unsigned i = 0; i < 3; i++)
		ma_sound_seek_to_pcm_frame(&sfx[i], 0);

	// 5. play all samples simultaniously
	for (unsigned i = 0; i < 3; i++)
		ma_sound_start(&sfx[i]);
	this_thread::sleep_for(1000ms);

	ma_engine_uninit(&engine);
	return 0;
}
