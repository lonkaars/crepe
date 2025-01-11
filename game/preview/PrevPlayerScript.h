#include <crepe/api/Animator.h>
#include <crepe/api/Config.h>
#include <crepe/api/Event.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/util/OptionalRef.h>

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

private:
	bool on_key_down(const crepe::KeyPressEvent & ev);
	bool on_key_up(const crepe::KeyReleaseEvent & ev);
	void help_kick(const crepe::vec2 & direction);

private:
	float & engine_gravity = crepe::Config::get_instance().physics.gravity;
	crepe::OptionalRef<crepe::Rigidbody> rb;
};
