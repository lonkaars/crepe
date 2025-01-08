#include <iostream>
#include "EnemyBulletScript.h"
#include <crepe/api/Camera.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Metadata.h>

#include "EnemyConfig.h"
using namespace crepe;
using namespace std;
void EnemyBulletScript::init(){
	this->subscribe<CollisionEvent>([this](const CollisionEvent& e) -> bool {
		return this->on_collide(e);
	});
}
void EnemyBulletScript::fixed_update(crepe::duration_t dt){
	Transform& transform = this->get_component<Transform>();
	Camera& camera = this->get_components_by_name<Camera>("camera").front();
	Transform& cam_transform = this->get_components_by_name<Transform>("camera").front();
	Rigidbody& bullet_body = this->get_component<Rigidbody>();
	//move
	transform.position.x += bullet_body.data.linear_velocity.x * dt.count();
	vec2 half_screen = camera.viewport_size / 2;
	float despawn_location = cam_transform.position.x - half_screen.x - 50;
	if(transform.position.x < despawn_location){
		this->despawn_bullet();
	}
}

void EnemyBulletScript::despawn_bullet(){
	Transform& transform = this->get_component<Transform>();
	Rigidbody& bullet_body = this->get_component<Rigidbody>();
	bullet_body.active = false;
	transform.position = ENEMY_BULLET_POOL_LOCATION;
}

bool EnemyBulletScript::on_collide(const CollisionEvent& e){
	//cout << "collision happened with " << e.info.other.metadata.tag << endl;
	this->despawn_bullet();
	return false;
}
