#include <crepe/api/Engine.h>
#include <crepe/api/Script.h>
#include <crepe/api/Config.h>

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
	recording_t recording;

	void update() {
		switch (i++) {
			default: break;
			case 10:
				logf("record start");
				replay.record_start();
				break;
			case 60:
				logf("record end, playing recording");
				this->recording = replay.record_end();
				replay.play(this->recording);
				break;
			case 61:
				logf("done, releasing recording");
				replay.release(this->recording);
				break;
			case 72:
				logf("exit");
				queue_event<ShutDownEvent>();
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
		scapegoat.add_component<BehaviorScript>().set_script<Timeline>();
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
