

#include <crepe/api/AssetManager.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Point.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/GameObject.h>
#include <crepe/RenderSystem.h>
#include <memory>

#include "chrono"

using namespace crepe::api;

int main() {
	auto cam = Camera(0, "MainCamera", "TAG", 0);
	auto & mgr = AssetManager::get_instance();
	Color color(0, 0, 0, 0);
	Point point = {
		.x = 0,
		.y = 0,
	};
	cam.add_component<Transform>(point, 0, 1);
	cam.add_component<Sprite>(std::make_shared<Texture>("../asset/texture/world.png"), color, FlipSettings{false, false});

	auto & sys = crepe::RenderSystem::get_instance();
	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
	}
}
