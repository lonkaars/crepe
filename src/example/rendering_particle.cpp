#include "api/Animator.h"
#include "api/Camera.h"
#include "api/LoopManager.h"
#include "api/LoopTimer.h"
#include "system/AnimatorSystem.h"
#include "system/ParticleSystem.h"
#include <SDL2/SDL_timer.h>
#include <crepe/ComponentManager.h>

#include <crepe/Component.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

/*
	auto & test = game_object.add_component<ParticleEmitter>(ParticleEmitter::Data{
		.position = {0, 0},
		.max_particles = 10,
		.emission_rate = 0.1,
		.min_speed = 6,
		.max_speed = 20,
		.min_angle = -20,
		.max_angle = 20,
		.begin_lifespan = 0,
		.end_lifespan = 60,
		.force_over_time = vec2{0, 0},
		.boundary{
			.width = 1000,
			.height = 1000,
			.offset = vec2{0, 0},
			.reset_on_exit = false,
		},
		.sprite = test_sprite,
	});
	*/

class TestScene : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject game_object = mgr.new_object("", "", vec2{0, 0}, 0, 1);

		Color color(255, 255, 255, 255);

		auto img = Texture("asset/spritesheet/spritesheet_test.png");

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img, color, Sprite::FlipSettings{true, true}, 1, 1, vec2{1, 1});

		//game_object.add_component<Animator>(test_sprite, 4, 1, 0).active = true;
		game_object.add_component<Animator>(test_sprite, 4, 1, 0).active = true;

		auto & cam = game_object.add_component<Camera>(Color::RED, ivec2{1280, 720},
													   vec2{2.59, 1.95}, 2.0);
	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	LoopManager engine;
	engine.add_scene<TestScene>();
	engine.start();

	/*
	game_object
		.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"), color,
		.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"), color,
							   FlipSettings{false, false})
		.order_in_layer
		= 6;
	*/

	return 0;
}
