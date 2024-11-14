#include <crepe/ComponentManager.h>
#include <crepe/api/AssetManager.h>

#include <crepe/Component.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	ComponentManager mgr;
	GameObject game_object = mgr.new_object("", "", Vector2{0, 0}, 0, 0);
	Color color(0, 0, 0, 0);
	Sprite test_sprite = game_object.add_component<Sprite>(
		make_shared<Texture>("asset/texture/img.png"), color,
		FlipSettings{true, true});
	game_object.add_component<ParticleEmitter>(ParticleEmitter::Data{
		.position = {0, 0},
		.max_particles = 100,
		.emission_rate = 0,
		.min_speed = 0,
		.max_speed = 0,
		.min_angle = 0,
		.max_angle = 0,
		.begin_lifespan = 0,
		.end_lifespan = 0,
		.force_over_time = Vector2{0, 0},
		.boundary{
			.width = 0,
			.height = 0,
			.offset = Vector2{0, 0},
			.reset_on_exit = false,
		},
		.sprite = test_sprite,
	});

	return 0;
}
