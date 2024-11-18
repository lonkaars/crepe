#include "api/Camera.h"
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/util/Log.h>

#include <crepe/api/AssetManager.h>
#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>

#include <chrono>
#include <memory>

using namespace std;
using namespace crepe;

int main() {
	dbg_trace();

	ComponentManager mgr{};
	RenderSystem sys{mgr};

	GameObject obj = mgr.new_object("name", "tag", Vector2{250, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("name", "tag", Vector2{500, 0}, 1, 0.1);
	GameObject obj2 = mgr.new_object("name", "tag", Vector2{800, 0}, 1, 0.1);

	// Normal adding components
	{
		Color color(0, 0, 0, 0);
		obj.add_component<Sprite>(make_shared<Texture>("../asset/texture/img.png"), color,
								  FlipSettings{false, false});
		Camera & cam = obj.add_component<Camera>(Color::get_red());

	}
	/*
	{
		Color color(0, 0, 0, 0);
		obj1.add_component<Sprite>(make_shared<Texture>("../asset/texture/second.png"), color,
								   FlipSettings{true, true});
	}
	*/

	/*
	{
		Color color(0, 0, 0, 0);
		auto img = mgr.cache<Texture>("../asset/texture/second.png");
		obj2.add_component<Sprite>(img, color, FlipSettings{true, true});
	}
	*/

	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
	}
}
