#include <gtest/gtest.h>
#include <memory>

#include <crepe/api/AudioSource.h>
#include <crepe/api/Asset.h>

#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

using namespace crepe::api;

// TODO: mock internal audio class

TEST(audio, play) {
	auto res = std::make_unique<Asset>("../mwe/audio/bgm.ogg");
	auto bgm = AudioSource(std::move(res));

	bgm.play();

	this_thread::sleep_for(2s);

	bgm.stop();

	ASSERT_TRUE(true);
}

