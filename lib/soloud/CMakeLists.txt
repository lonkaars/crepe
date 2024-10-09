cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(WITH_SDL2)

add_subdirectory(../sdl2 sdl2)

project(soloud C CXX)

add_library(soloud SHARED
	src/src/audiosource/ay/chipplayer.cpp
	src/src/audiosource/ay/sndbuffer.cpp
	src/src/audiosource/ay/sndchip.cpp
	src/src/audiosource/ay/sndrender.cpp
	src/src/audiosource/ay/soloud_ay.cpp
	src/src/audiosource/monotone/soloud_monotone.cpp
	src/src/audiosource/noise/soloud_noise.cpp
	src/src/audiosource/openmpt/soloud_openmpt.cpp
	src/src/audiosource/openmpt/soloud_openmpt_dll.c
	src/src/audiosource/sfxr/soloud_sfxr.cpp
	src/src/audiosource/speech/darray.cpp
	src/src/audiosource/speech/klatt.cpp
	src/src/audiosource/speech/resonator.cpp
	src/src/audiosource/speech/soloud_speech.cpp
	src/src/audiosource/speech/tts.cpp
	src/src/audiosource/tedsid/sid.cpp
	src/src/audiosource/tedsid/soloud_tedsid.cpp
	src/src/audiosource/tedsid/ted.cpp
	src/src/audiosource/vic/soloud_vic.cpp
	src/src/audiosource/vizsn/soloud_vizsn.cpp
	src/src/audiosource/wav/dr_impl.cpp
	src/src/audiosource/wav/soloud_wav.cpp
	src/src/audiosource/wav/soloud_wavstream.cpp
	src/src/audiosource/wav/stb_vorbis.c

	src/src/backend/alsa/soloud_alsa.cpp
	src/src/backend/coreaudio/soloud_coreaudio.cpp
	src/src/backend/jack/soloud_jack.cpp
	src/src/backend/miniaudio/soloud_miniaudio.cpp
	src/src/backend/nosound/soloud_nosound.cpp
	src/src/backend/null/soloud_null.cpp
	src/src/backend/openal/soloud_openal.cpp
	src/src/backend/openal/soloud_openal_dll.c
	src/src/backend/opensles/soloud_opensles.cpp
	src/src/backend/oss/soloud_oss.cpp
	src/src/backend/portaudio/soloud_portaudio.cpp
	src/src/backend/portaudio/soloud_portaudio_dll.c
	src/src/backend/sdl/soloud_sdl1.cpp
	src/src/backend/sdl/soloud_sdl1_dll.c
	src/src/backend/sdl/soloud_sdl2.cpp
	src/src/backend/sdl/soloud_sdl2_dll.c
	src/src/backend/sdl2_static/soloud_sdl2_static.cpp
	src/src/backend/sdl_static/soloud_sdl_static.cpp
	src/src/backend/wasapi/soloud_wasapi.cpp
	src/src/backend/winmm/soloud_winmm.cpp
	src/src/backend/xaudio2/soloud_xaudio2.cpp

	src/src/core/soloud.cpp
	src/src/core/soloud_audiosource.cpp
	src/src/core/soloud_bus.cpp
	src/src/core/soloud_core_3d.cpp
	src/src/core/soloud_core_basicops.cpp
	src/src/core/soloud_core_faderops.cpp
	src/src/core/soloud_core_filterops.cpp
	src/src/core/soloud_core_getters.cpp
	src/src/core/soloud_core_setters.cpp
	src/src/core/soloud_core_voicegroup.cpp
	src/src/core/soloud_core_voiceops.cpp
	src/src/core/soloud_fader.cpp
	src/src/core/soloud_fft.cpp
	src/src/core/soloud_fft_lut.cpp
	src/src/core/soloud_file.cpp
	src/src/core/soloud_filter.cpp
	src/src/core/soloud_misc.cpp
	src/src/core/soloud_queue.cpp
	src/src/core/soloud_thread.cpp

	# src/src/filter/soloud_bassboostfilter.cpp
	# src/src/filter/soloud_biquadresonantfilter.cpp
	# src/src/filter/soloud_dcremovalfilter.cpp
	# src/src/filter/soloud_duckfilter.cpp
	# src/src/filter/soloud_echofilter.cpp
	# src/src/filter/soloud_eqfilter.cpp
	# src/src/filter/soloud_fftfilter.cpp
	# src/src/filter/soloud_flangerfilter.cpp
	# src/src/filter/soloud_freeverbfilter.cpp
	# src/src/filter/soloud_lofifilter.cpp
	# src/src/filter/soloud_robotizefilter.cpp
	# src/src/filter/soloud_waveshaperfilter.cpp
)
target_include_directories(soloud PRIVATE src/include)
target_include_directories(soloud SYSTEM INTERFACE src/include)

target_link_libraries(soloud PRIVATE SDL2)

