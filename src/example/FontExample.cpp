#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <crepe/api/Camera.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Text.h>
#include <crepe/facade/Font.h>
#include <crepe/facade/SDLContext.h>
#include <crepe/manager/EventManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/manager/ResourceManager.h>
#include <exception>
#include <iostream>
#include <memory>
using namespace crepe;
using namespace std;
using namespace std::chrono;
class TestScript : public Script {
public:
	steady_clock::time_point start_time;
	virtual void init() override { start_time = steady_clock::now(); }
	virtual void update() override {
		auto now = steady_clock::now();
		auto elapsed = duration_cast<seconds>(now - start_time).count();

		if (elapsed >= 5) {
			Mediator & med = mediator;
			EventManager & event_mgr = med.event_manager;
			event_mgr.trigger_event<ShutDownEvent>();
		}
	}
};
class TestScene : public Scene {
public:
	void load_scene() override {
		GameObject text_object = this->new_object("test", "test", vec2{0, 0}, 0, 1);
		text_object.add_component<Text>(vec2(100, 100), vec2(0, 0), "OpenSymbol",
										Text::Data{});
		text_object.add_component<BehaviorScript>().set_script<TestScript>();
		text_object.add_component<Camera>(ivec2{300, 300}, vec2{100, 100}, Camera::Data{});
	}
	std::string get_name() const override { return "hey"; }
};
int main() {
	// Config& config = Config::get_instance();
	// config.log.level = Log::Level::TRACE;
	LoopManager engine;
	engine.add_scene<TestScene>();
	engine.start();

	return 0;
}
