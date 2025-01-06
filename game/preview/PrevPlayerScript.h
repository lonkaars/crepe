
#include <crepe/api/Event.h>
#include <crepe/api/Script.h>
#include <crepe/util/OptionalRef.h>

#include <crepe/api/Animator.h>
#include <crepe/api/Sprite.h>

class PrevPlayerScript : public crepe::Script {
private:
	crepe::OptionalRef<crepe::Animator> head_anim;
	crepe::OptionalRef<crepe::Animator> body_anim;
	crepe::OptionalRef<crepe::Sprite> head;
	crepe::OptionalRef<crepe::Sprite> body;

private:
	float move_speed = 100;

private:
	void init();
	void fixed_update(crepe::duration_t dt);
	bool key_pressed(const crepe::KeyPressEvent & ev);
};
