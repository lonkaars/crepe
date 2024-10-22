


#include <crepe/util/log.h>
#include <crepe/GameObject.h>
#include <crepe/ComponentManager.h>
#include <crepe/RenderSystem.h>


#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Point.h>


#include <memory>
#include <chrono>


using namespace std;
using namespace crepe;
using namespace crepe::api;

int main(){

	dbg_trace();


	auto obj = GameObject(0, "name" , "tag", 0);

	Color color(0,0,0,0);
	//Sprite sprite(std::move(texture), color, {false,false});

	Point point = {
		.x = 0,
		.y = 0,
	};

	obj.add_component<Transform>(point, 0 ,1);
	obj.add_component<Sprite>(make_unique<Texture>("../asset/texture/img.png"),color, flip_settings{false,false});

	auto& sys = crepe::RenderSystem::get_instance();

	// scene example
	auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
    }

}

