#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
private:
	class TestSoundContext : public SoundContext {
	public:
		MOCK_METHOD(Sound::Handle, play, (Sound & resource), (override));
		MOCK_METHOD(void, stop, (Sound::Handle &), (override));
		MOCK_METHOD(void, set_volume, (Sound &, Sound::Handle &, float), (override));
		MOCK_METHOD(void, set_loop, (Sound &, Sound::Handle &, bool), (override));
	};

	class TestAudioSystem : public AudioSystem {
	public:
		using AudioSystem::AudioSystem;
		StrictMock<TestSoundContext> context;
		virtual SoundContext & get_context() {
			return this->context;
		}
	};

private:
	Mediator mediator;
	ComponentManager component_manager{mediator};
	ResourceManager resource_manager{mediator};
public:
	TestAudioSystem system {mediator};
	TestSoundContext & context = system.context;

private:
	GameObject entity = component_manager.new_object("name");
public:
	AudioSource & component = entity.add_component<AudioSource>("mwe/audio/bgm.ogg");
};

TEST_F(AudioTest, Default) {
	EXPECT_CALL(context, play(_)).Times(0);
	EXPECT_CALL(context, stop(_)).Times(0);
	EXPECT_CALL(context, set_volume(_, _, _)).Times(0);
	EXPECT_CALL(context, set_loop(_, _, _)).Times(0);
	system.update();
}

TEST_F(AudioTest, Play) {
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, play(_)).Times(0);
		component.play();
	}

	{
		InSequence seq;

		EXPECT_CALL(context, play(_)).Times(1);
		system.update();
	}
}

TEST_F(AudioTest, Stop) {
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, stop(_)).Times(0);
		component.stop();
	}

	{
		InSequence seq;

		EXPECT_CALL(context, stop(_)).Times(1);
		system.update();
	}
}

TEST_F(AudioTest, Volume) {
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, set_volume(_, _, _)).Times(0);
		component.volume += 0.2;
	}

	{
		InSequence seq;

		EXPECT_CALL(context, set_volume(_, _, component.volume)).Times(1);
		system.update();
	}
}

TEST_F(AudioTest, Looping) {
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, set_loop(_, _, _)).Times(0);
		component.loop = !component.loop;
	}

	{
		InSequence seq;

		EXPECT_CALL(context, set_loop(_, _, component.loop)).Times(1);
		system.update();
	}
}

TEST_F(AudioTest, StopOnDeactivate) {
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, stop(_)).Times(1);
		component.active = false;
		system.update();
	}
}

TEST_F(AudioTest, PlayOnActive) {
	component.active = false;
	component.play_on_awake = true;
	system.update();

	{
		InSequence seq;

		EXPECT_CALL(context, play(_)).Times(1);
		component.active = true;
		system.update();
	}
}

