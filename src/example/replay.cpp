#include "util/OptionalRef.h"
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
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>

using namespace crepe;
using namespace std;

class AnimationScript : public Script {
	Transform * transform;
	float t = 0;

	void init() {
		Log::logf("AnimationScript init");
		transform = &get_component<Transform>();
	}

	void update() {
		Log::logf("AnimationScript update");
		t += 0.01;
		transform->position = { sin(t), cos(t) };
	}
};

class TestScene : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		Log::logf("Initializing scene...");
		Mediator & m = this->mediator;
		ComponentManager & mgr = m.component_manager;


		GameObject cam = mgr.new_object("cam");
		cam.add_component<Camera>(ivec2{640,480},vec2{3,3}, Camera::Data{
			.bg_color = Color::WHITE,
		});

		GameObject square = mgr.new_object("square");
		Texture texture{"asset/texture/square.png"};
		square.add_component<Sprite>(texture, Sprite::Data{
			.size = { 0.5, 0.5 },
		});
		square.add_component<BehaviorScript>().set_script<AnimationScript>();
		Log::logf("Done initializing scene");
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	LoopManager gameloop;

	gameloop.add_scene<TestScene>();
	gameloop.start();
	return 0;
}
