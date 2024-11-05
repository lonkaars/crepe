#include <crepe/ComponentManager.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/api/GameObject.h>
#include <crepe/util/log.h>

#include <crepe/api/AssetManager.h>
#include <crepe/api/Color.h>
#include <crepe/api/Point.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>

#include <chrono>
#include <memory>

using namespace std;
using namespace crepe;

int main() {

	dbg_trace();

	auto obj = GameObject(0, "name", "tag", 0);
	auto obj1 = GameObject(1, "name", "tag", 0);
	auto obj2 = GameObject(2, "name", "tag", 0);

	auto & mgr = AssetManager::get_instance();
	// Normal adding components
	{
		Color color(0, 0, 0, 0);
		Point point = {
			.x = 0,
			.y = 0,
		};
		obj.add_component<Transform>(point, 1, 1);
		obj.add_component<Sprite>(
			make_shared<Texture>("../asset/texture/img.png"), color,
			FlipSettings{true, true});
	}

	{
		Color color(0, 0, 0, 0);
		Point point = {
			.x = 500,
			.y = 0,
		};
		obj1.add_component<Transform>(point, 0, 0.1);
		auto img = mgr.cache<Texture>("../asset/texture/second.png");
		obj1.add_component<Sprite>(img, color, FlipSettings{true, true});
	}

	{
		Color color(0, 0, 0, 0);
		Point point = {
			.x = 800,
			.y = 0,
		};
		//obj.add_component<Transform>(point, 0, 0.1);
		auto img = mgr.cache<Texture>("../asset/texture/second.png");
		obj2.add_component<Sprite>(img, color, FlipSettings{true, true});
	}

	auto & sys = crepe::RenderSystem::get_instance();
	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
	}
}
