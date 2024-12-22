#pragma once

#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>

class PlayerObject : public crepe::GameObject {
public:
	PlayerObject(crepe::GameObject &&);

public:
	struct {
		crepe::Sprite & body;
		crepe::Sprite & head;
		crepe::Sprite & jetpack;
	} sprite;

	struct {
		crepe::Animator & body;
		crepe::Animator & head;
		crepe::Animator & jetpack;
	} animator;

	crepe::Rigidbody & body;
	crepe::BoxCollider & collider;
	crepe::BehaviorScript & controller;
};
