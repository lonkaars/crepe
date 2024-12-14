#include <crepe/util/Log.h>
#include <crepe/api/Engine.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Camera.h>

using namespace crepe;
using namespace std;

class DemoScene : public Scene {
	string get_name() const override { return "DemoScene"; }
	void load_scene() override {
		GameObject camera = new_object("camera");
		camera.add_component<Camera>(vec2{10, 10}, Camera::Data{});
	}
};

int main() {
	Engine demo;

	demo.add_scene<DemoScene>();

	return demo.main();
}

