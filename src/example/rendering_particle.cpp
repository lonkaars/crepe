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

		auto img = Texture("asset/spritesheet/pokemon_spritesheet.png");

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img, Sprite::Data{
					 .color = color,
					 .flip = Sprite::FlipSettings{false, false},
					 .sorting_in_layer = 2,
					 .order_in_layer = 2,
					 .size = {0, 100},
					 .angle_offset = 0,
					 .scale = 1,
				 });

		auto & anim = game_object.add_component<Animator>(Animator::Data{
			.spritesheet = test_sprite,
			.col = 4,
			.row = 4,
			.fps = 10,
		});

		auto & cam = game_object.add_component<Camera>(Color::WHITE, ivec2{720, 1280},
													   vec2{400, 400}, 1.0);
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
