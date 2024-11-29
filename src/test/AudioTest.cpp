#include <gtest/gtest.h>
#include <future>

#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/ResourceManager.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/GameObject.h>
#include <crepe/system/AudioSystem.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;
using namespace testing;

class AudioTest : public Test {
	Mediator mediator;
public:
	ComponentManager component_manager{mediator};
	ResourceManager resource_manager{mediator};
	AudioSystem system {mediator};

private:
	GameObject entity = component_manager.new_object("name");
public:
	AudioSource & bgm = entity.add_component<AudioSource>("mwe/audio/bgm.ogg");
	AudioSource & sfx1 = entity.add_component<AudioSource>("mwe/audio/sfx1.wav");
	AudioSource & sfx2 = entity.add_component<AudioSource>("mwe/audio/sfx2.wav");
	AudioSource & sfx3 = entity.add_component<AudioSource>("mwe/audio/sfx3.wav");

};

TEST_F(AudioTest, Default) {
	bool example_done = false;

	future example = async([&](){
		// Start the background track
		bgm.play();

		// Play each sample sequentially while pausing and resuming the background track
		this_thread::sleep_for(500ms);
		sfx1.play();
		this_thread::sleep_for(500ms);
		sfx2.play();
		bgm.stop();
		this_thread::sleep_for(500ms);
		sfx3.play();
		bgm.play();
		this_thread::sleep_for(500ms);

		// Play all samples simultaniously
		sfx1.play();
		sfx2.play();
		sfx3.play();
		this_thread::sleep_for(1000ms);
	});

	future system_loop = async([&](){
		while (!example_done) {
			auto next = chrono::steady_clock::now() + 25ms;
			system.update();
			this_thread::sleep_until(next);
		}
	});

	example.wait();
	example_done = true;
	system_loop.wait();
}

