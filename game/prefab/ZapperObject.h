#pragma once

#include <crepe/api/Animator.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>

class ZapperObject : public crepe::GameObject {
public:
	ZapperObject(crepe::GameObject &&);

public:
	struct {
		crepe::Sprite & orb_start;
		crepe::Sprite & orb_end;
		crepe::Sprite & glow_start;
		crepe::Sprite & glow_end;
		crepe::Sprite & beam;
	} sprite;

	struct {
		crepe::Animator & orb_start;
		crepe::Animator & orb_end;
		crepe::Animator & glow_start;
		crepe::Animator & glow_end;
	} animator;

	// crepe::Rigidbody & body;
	// crepe::BoxCollider & collider;

private:
	static constexpr float SCALE = 0.8;

public:
	void place(const crepe::vec2 & position, float rotation, float length);
};
