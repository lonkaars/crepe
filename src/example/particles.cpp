#include <crepe/ComponentManager.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/api/AssetManager.h>
#include <crepe/system/PhysicsSystem.h>

#include <crepe/Component.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Color.h>


using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	
	GameObject *game_object = new GameObject(0, "Name", "Tag", Vector2{0,0},0,0);
	game_object->add_component<ParticleEmitter>(ParticleEmitter::ParticleEmitterData{
		.position = {0,0},
		.max_particles = 0,
		.emission_rate = 0,
		.min_speed = 0,
		.max_speed = 0,
		.min_angle = 0,
		.max_angle = 0,
		.begin_lifespan = 0,
		.end_lifespan = 0,
		.force_over_time = Vector2{0,0},
		.boundary{
			.boundary_width = 0,
			.boundary_height = 0,
			.boundary_offset = Vector2{0,0},
			.reset_on_exit = false,
		},
		.sprite = nullptr,
	});

	return 0;
}
