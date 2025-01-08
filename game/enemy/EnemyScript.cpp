#include <iostream>
#include "../Config.h"
#include "EnemyScript.h"
#include <crepe/api/Animator.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/AI.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>
using namespace crepe;
using namespace std;
EnemyScript::EnemyScript(){
	//cout << column << std::endl;
	engine.seed(rd());
	this->last_fired = std::chrono::steady_clock::now();
}
void EnemyScript::init(){
	Metadata& meta = this->get_component<Metadata>();
	this->subscribe<SpawnEnemyEvent>([this](const SpawnEnemyEvent& e) -> bool{
		return this->spawn_enemy(e);
	},meta.game_object_id);
};
void EnemyScript::fixed_update(duration_t dt) {
	
    Transform& transform = this->get_component<Transform>();
    Transform& player_transform = this->get_components_by_name<Transform>("player").front();
    AI& ai_component = this->get_component<AI>();

    float direction_to_player_y = player_transform.position.y - transform.position.y;
	float distance_to_player_y = std::abs(direction_to_player_y);

	float adjustment_speed = speed * (distance_to_player_y / MAX_DISTANCE);

	adjustment_speed = std::clamp(adjustment_speed, MIN_SPEED, MAX_SPEED);
	//cout  << "speed: "<< adjustment_speed << endl;
	//cout  << "direction: " << direction_to_player_y << endl;
	// Move the path nodes on the Y-axis
	for (vec2& path_node : ai_component.path) {
		path_node.y += (direction_to_player_y > 0 ? 1 : -1) * adjustment_speed * dt.count();
	}
	//bullet fire logic:

	auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - last_fired;
	if (elapsed > std::chrono::duration<float>(5)) {
    	this->shoot(transform.position,0);
		last_fired = now;
	}

}
bool EnemyScript::spawn_enemy(const SpawnEnemyEvent& e){
	this->speed = e.speed;
	AI& ai_component = this->get_component<AI>();
	Transform& transform = this->get_component<Transform>();
	Camera& camera = this->get_components_by_name<Camera>("camera").front();
	Transform& cam_transform = this->get_components_by_name<Transform>("camera").front();
	vec2 half_screen = camera.viewport_size / 2;
	//cout << "column: " << e.column << endl;
	float x_value = cam_transform.position.x + half_screen.x - 50 * (1 + e.column);  
		uniform_real_distribution<float> dist(
		cam_transform.position.y - half_screen.y + 100,
		cam_transform.position.y + half_screen.y - 100
		);
	float random_height = dist(engine);
	vec2 spawn_location = {cam_transform.position.x + camera.viewport_size.x / 2 + 100,random_height};
	transform.position = spawn_location;
	// transform.position = vec2{cam_transform}
	ai_component.path.clear();
	ai_component.make_oval_path(10, 10, vec2{x_value,random_height}, 1.5708, true);
	
	return true;
}

void EnemyScript::onCollide(const CollisionEvent & collisionData){

}

void EnemyScript::shoot(const vec2& location,float angle){
	//cout << "enemy shot" << endl;
	RefVector<Transform> bullet_transforms = this->get_components_by_tag<Transform>("EnemyBullet");

	for(Transform& bullet_pos : bullet_transforms){
		//cout << "bullet pos  x: " << bullet_pos.position.x << " y: " << bullet_pos.position.y << endl;
		if(bullet_pos.position.x == 0 && bullet_pos.position.y == -750){

			bullet_pos.position = location;
			bullet_pos.position.x -= 20;
			Rigidbody& bullet_body = this->get_components_by_id<Rigidbody>(bullet_pos.game_object_id).front();
			BoxCollider bullet_collider = this->get_components_by_id<BoxCollider>(bullet_pos.game_object_id).front();
			bullet_collider.active = true;
			bullet_body.active = true;
			return;
		}
	}
}
