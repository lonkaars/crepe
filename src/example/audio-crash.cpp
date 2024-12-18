#include <crepe/api/LoopManager.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Camera.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/Config.h>

#define private public
#include <crepe/api/Script.h>

using namespace crepe;
using namespace std;

class Auto : public Script {
	unsigned i = 0;
	void init() {
		AudioSource & sound = get_component<AudioSource>();
		sound.play();
	}

	void update() {
		if (++i < 50) return;
		EventManager & evmgr = this->mediator->event_manager;
		evmgr.trigger_event<ShutDownEvent>();
	}
};

class Bug : public Scene {
	virtual std::string get_name() const override { return "bug"; }
	void load_scene() override {
		GameObject camera = new_object("camera");
		camera.add_component<Camera>(ivec2{10, 10}, vec2{1, 1}, Camera::Data{ });

		GameObject sound = new_object("sound");
		sound.add_component<AudioSource>(Asset{"mwe/audio/bgm.ogg"});
		sound.add_component<BehaviorScript>().set_script<Auto>();
	}
};

int main() {
	Config & config = Config::get_instance();
	config.log.level = Log::Level::TRACE;

	LoopManager example;
	example.add_scene<Bug>();
	example.start();
	return 0;
}
