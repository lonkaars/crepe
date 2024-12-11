#include <crepe/util/OptionalRef.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Config.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Engine.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/manager/ReplayManager.h>

using namespace crepe;
using namespace std;

class AnimationScript : public Script {
	Transform * transform;
	float t = 0;

	void init() {
		transform = &get_component<Transform>();
	}

	void update() {
		t += 0.05;
		transform->position = { sin(t), cos(t) };
	}
};

class Timeline : public Script {
	unsigned i = 0;
	ReplayManager & mgr;
	recording_t recording;

public:
	Timeline(ReplayManager & mgr)
		: mgr(mgr) {}

	void update() {
		switch (i++) {
			default: break;
			case 10:
							 mgr.record_start();
							 break;
			case 60:
							 this->recording = mgr.record_end();
							 break;
			case 70:
							 mgr.play(this->recording);
							 break;
			case 71:
							 mgr.release(this->recording);
							 break;
			case 72:
							 throw;
							 break;
		};
	}
};

class TestScene : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		Mediator & mediator = this->mediator;
		ComponentManager & mgr = mediator.component_manager;

		GameObject cam = mgr.new_object("cam");
		cam.add_component<Camera>(ivec2{640,480},vec2{3,3}, Camera::Data{
			.bg_color = Color::WHITE,
		});

		GameObject square = mgr.new_object("square");
		square.add_component<Sprite>(
			Asset{"asset/texture/square.png"},
			Sprite::Data{
				.size = { 0.5, 0.5 },
			}
		);
		square.add_component<BehaviorScript>().set_script<AnimationScript>();

		GameObject scapegoat = mgr.new_object("");
		scapegoat.add_component<BehaviorScript>().set_script<Timeline>(mediator.replay_manager);
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	Config & cfg = Config::get_instance();
	cfg.log.level = Log::Level::DEBUG;

	Engine engine;

	engine.add_scene<TestScene>();
	engine.start();
	return 0;
}
