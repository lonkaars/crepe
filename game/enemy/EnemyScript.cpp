#include "EnemyScript.h"
#include "../Config.h"
#include "../Random.h"
#include "../enemy/EnemyConfig.h"
#include "api/Color.h"
#include "api/Sprite.h"
#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>
#include <random>
using namespace crepe;
using namespace std;
EnemyScript::EnemyScript() {
	engine.seed(rd());
	this->last_fired = std::chrono::steady_clock::now();
	this->shot_delay = std::chrono::duration<float>(3 + Random::f(1, 0));
}
void EnemyScript::init() {
	Metadata & meta = this->get_component<Metadata>();
	this->subscribe<SpawnEnemyEvent>(
		[this](const SpawnEnemyEvent & e) -> bool { return this->spawn_enemy(e); },
		meta.game_object_id
	);
	this->subscribe<CollisionEvent>([this](const CollisionEvent & e) -> bool {
		return this->on_collide(e);
	});
};
void EnemyScript::fixed_update(duration_t dt) {
	if (!spawned) return;
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed_hit = now - last_hit;
	//hit blink timer
	if (elapsed_hit > blink_time) {
		set_hit_blink(false);
	}
	Transform & transform = this->get_component<Transform>();
	if (!this->alive) {
		Camera & camera = this->get_components_by_name<Camera>("camera").front();
		Transform & cam_transform = this->get_components_by_name<Transform>("camera").front();
		vec2 half_screen = camera.viewport_size / 2;
		float x_value = cam_transform.position.x - half_screen.x - 100;
		if (transform.position.x < x_value) {
			this->despawn_enemy();
		}
		return;
	}

	Transform & player_transform = this->get_components_by_name<Transform>("player").front();
	Rigidbody & enemy_body = this->get_component<Rigidbody>();
	AI & ai_component = this->get_component<AI>();

	float direction_to_player_y = player_transform.position.y - transform.position.y;
	float distance_to_player_y = std::abs(direction_to_player_y);

	float adjustment_speed = speed * (distance_to_player_y / MAX_DISTANCE);
	adjustment_speed = std::clamp(adjustment_speed, MIN_SPEED, MAX_SPEED);
	Rigidbody & player_body = this->get_components_by_tag<Rigidbody>("player").front();
	// move path nodes
	for (vec2 & path_node : ai_component.path) {
		path_node.y += (direction_to_player_y > 0 ? 1 : -1) * adjustment_speed * dt.count();
		path_node.x += player_body.data.linear_velocity.x * dt.count();
	}
	//bullet fire logic:

	std::chrono::duration<float> elapsed = now - last_fired;
	if (elapsed > shot_delay) {
		this->shoot(transform.position);
		last_fired = now;
		this->shot_delay = std::chrono::duration<float>(Random::f(4, 1.5));
	}
}

bool EnemyScript::spawn_enemy(const SpawnEnemyEvent & e) {

	this->speed = e.speed;
	this->alive = true;
	this->spawned = true;
	this->health = 2;
	RefVector<Animator> animators = this->get_components<Animator>();
	for (Animator & anim : animators) {
		anim.active = false;
		anim.set_anim(0);
	}
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for (Sprite & sprite : sprites) {
		sprite.data.position_offset.x = 0;
	}
	Sprite & jetpack = sprites[2];
	jetpack.data.position_offset.x = 20;
	Sprite & gun = sprites[3];
	gun.data.position_offset.x = -20;
	AI & ai_component = this->get_component<AI>();
	Transform & transform = this->get_component<Transform>();
	Camera & camera = this->get_components_by_name<Camera>("camera").front();
	Transform & cam_transform = this->get_components_by_name<Transform>("camera").front();
	Rigidbody& rb = this->get_component<Rigidbody>();
	rb.data.collision_layers = {COLL_LAY_BOT_TOP, COLL_LAY_PLAYER_BULLET};
	rb.data.collision_layer = COLL_LAY_ENEMY;
	vec2 half_screen = camera.viewport_size / 2;
	float x_value = cam_transform.position.x + half_screen.x - 40 * (1 + e.column);
	uniform_real_distribution<float> dist(
		cam_transform.position.y - half_screen.y + 100,
		cam_transform.position.y + half_screen.y - 100
	);
	float random_height = dist(engine);
	vec2 spawn_location
		= {cam_transform.position.x + camera.viewport_size.x / 2 + 100, random_height};
	transform.position = spawn_location;
	ai_component.path.clear();
	ai_component.make_oval_path(10, 30, vec2 {x_value, random_height}, 1.5708, true);
	ai_component.active = true;
	this->last_fired = std::chrono::steady_clock::now();

	return false;
}

void EnemyScript::set_hit_blink(bool status) {
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for (Sprite & sprite : sprites) {
		if (status) {
			sprite.data.color = Color::RED;
			continue;
		}
		sprite.data.color = Color::WHITE;
	}
}

bool EnemyScript::on_collide(const CollisionEvent & e) {
	if (!this->alive) return false;
	if (e.info.other.metadata.tag == "player_bullet") {
		this->health--;
		last_hit = std::chrono::steady_clock::now();
		//Sprite& sprite;
		set_hit_blink(true);
		if (health <= 0) {
		this->death();
	}
	}
	
	//body_animator.play();

	return false;
}
void EnemyScript::death() {

	Rigidbody & rb = this->get_component<Rigidbody>();
	Transform & tr = this->get_component<Transform>();
	RefVector<Animator> animators = this->get_components<Animator>();
	for (Animator & anim : animators) {
		anim.active = false;
		anim.set_anim(3);
	}
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	for (Sprite & sprite : sprites) {
		sprite.data.position_offset.x = 15;
	}
	rb.data.linear_velocity_coefficient = {0.5, 1};
	rb.data.collision_layers = {COLL_LAY_BOT_TOP};
	rb.data.collision_layer = 0;

	rb.data.gravity_scale = 1;
	tr.rotation = 90;
	AI & ai = this->get_component<AI>();
	ai.active = false;
	this->alive = false;
	AI & ai_component = this->get_component<AI>();
	ai_component.active = false;
}
void EnemyScript::despawn_enemy() {
	Transform & transform = this->get_component<Transform>();
	Rigidbody & rb = this->get_component<Rigidbody>();
	rb.data.gravity_scale = 0;
	rb.data.linear_velocity = {0, 0};
	transform.rotation = 0;
	transform.position = ENEMY_POOL_LOCATION;

	this->spawned = false;
}

void EnemyScript::shoot(const vec2 & location) {
	RefVector<Transform> bullet_transforms
		= this->get_components_by_tag<Transform>("enemy_bullet");

	for (Transform & bullet_pos : bullet_transforms) {
		if (bullet_pos.position.x == 0 && bullet_pos.position.y == -750) {

			bullet_pos.position = location;
			bullet_pos.position.x -= 20;
			Rigidbody & bullet_body
				= this->get_components_by_id<Rigidbody>(bullet_pos.game_object_id).front();
			BoxCollider bullet_collider
				= this->get_components_by_id<BoxCollider>(bullet_pos.game_object_id).front();
			bullet_collider.active = true;
			bullet_body.active = true;
			AudioSource & audio = this->get_component<AudioSource>();
			audio.play();
			return;
		}
	}
}
