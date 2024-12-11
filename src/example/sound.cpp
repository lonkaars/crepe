

#include "api/Asset.h"
#include "api/AudioSource.h"
#include "api/BehaviorScript.h"
#include "api/Camera.h"
#include "api/GameObject.h"
#include "api/LoopManager.h"
#include "api/Scene.h"
#include "api/Script.h"
#include "manager/ComponentManager.h"
#include "types.h"
#include <string>

using namespace crepe;


class ScriptTest : public Script {
	void init(){
		auto & audio = this->get_component<AudioSource>();
		audio.play();
	}
	void update(){
	}
};


class TestSound : public Scene {
public: 
	void load_scene(){
		Mediator & mediator = this->mediator;
		ComponentManager & mgr = mediator.component_manager;

		GameObject obj = mgr.new_object("SOUND");
		GameObject cam = mgr.new_object("cam");
		cam.add_component<Camera>(ivec2{100,100},vec2{100,100}, Camera::Data{});

		Asset asset{"asset/audio/sample.ogg"};
		auto & test = obj.add_component<AudioSource>(asset);
		obj.add_component<BehaviorScript>().set_script<ScriptTest>();


	}

	std::string get_name() const { return "TestScene"; };

};

int main(){
	LoopManager engine;
	engine.add_scene<TestSound>();
	engine.start();
	return 0;
}
