

#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>
#include <crepe/RenderSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/Color.h>
#include <crepe/api/Point.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/AssetManager.h>

#include <chrono>
#include <memory>

using namespace std;
using namespace crepe;
using namespace crepe::api;

int main() {

	dbg_trace();

	auto obj = GameObject(0, "name", "tag", 0);
	auto obj1= GameObject(0, "name", "tag", 0);
	auto obj2 = GameObject(0, "name", "tag", 0);

	auto& mgr = AssetManager::get_instance();
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
			flip_settings{true, true});
	}
	{
		Color color(0, 0, 0, 0);
		Point point = {
			.x = 500,
			.y = 0,
		};
		obj.add_component<Transform>(point, 0, 0.1);
		auto img = mgr.cache<Texture>("../asset/texture/second.png");	
		obj.add_component<Sprite>(img, color,
			flip_settings{true, true});
	}
	{
		Color color(0, 0, 0, 0);
		Point point = {
			.x = 800,
			.y = 0,
		};
		//obj.add_component<Transform>(point, 0, 0.1);
		auto img = mgr.cache<Texture>("../asset/texture/second.png");	
		obj.add_component<Sprite>(img, color,
			flip_settings{true, true});
	}




	auto & sys = crepe::RenderSystem::get_instance();
	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
	}
}
