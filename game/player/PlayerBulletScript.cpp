#include <iostream>

#include <crepe/api/Camera.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Metadata.h>

#include "PlayerBulletScript.h"

using namespace crepe;
using namespace std;
void PlayerBulletScript::init(){
	this->subscribe<CollisionEvent>([this](const CollisionEvent& e) -> bool {
		return this->on_collide(e);
	});
}
void PlayerBulletScript::fixed_update(crepe::duration_t dt){
	Transform& transform = this->get_component<Transform>();
	Camera& camera = this->get_components_by_name<Camera>("camera").front();
	Transform& cam_transform = this->get_components_by_name<Transform>("camera").front();
	Rigidbody& bullet_body = this->get_component<Rigidbody>();
	transform.rotation += bullet_body.data.angular_velocity;
	transform.position += bullet_body.data.linear_velocity * dt.count();
	vec2 half_screen = camera.viewport_size / 2;
	float despawn_location = cam_transform.position.x + half_screen.x + 50;
	if(transform.position.x > despawn_location){
		this->despawn_bullet();
	}
}

void PlayerBulletScript::despawn_bullet(){
	Transform& transform = this->get_component<Transform>();
	Rigidbody& bullet_body = this->get_component<Rigidbody>();
	bullet_body.active = false;
	BehaviorScript& bullet_script = this->get_component<BehaviorScript>();
	bullet_script.active = false;
	transform.position = {0,-850};
}

bool PlayerBulletScript::on_collide(const CollisionEvent& e){
	cout << "player bullet collision happened with " << e.info.other.metadata.tag << endl;
	this->despawn_bullet();
	return false;
}
