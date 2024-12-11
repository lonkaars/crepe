#include <crepe/util/OptionalRef.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
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
	OptionalRef<ReplayManager> mgr;
	recording_t recording;
	void update() {
		ReplayManager & mgr = this->mgr;
		switch (i++) {
			default: break;
			case 10:
							 // mgr.record_start();
							 Log::logf("start");
							 break;
			case 60:
							 // this->recording = mgr.record_end();
							 Log::logf("stop");
							 break;
			case 70:
							 // mgr.play(this->recording);
							 Log::logf("play");
							 break;
			case 71:
							 // mgr.release(this->recording);
							 Log::logf("end");
							 break;
			case 72:
							 Log::logf("exit");
							 throw;
							 break;
		};
	}
};

class TestScene : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		Mediator & m = this->mediator;
		ComponentManager & mgr = m.component_manager;

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
		scapegoat.add_component<BehaviorScript>().set_script<Timeline>();
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	LoopManager gameloop;

	gameloop.add_scene<TestScene>();
	gameloop.start();
	return 0;
}
