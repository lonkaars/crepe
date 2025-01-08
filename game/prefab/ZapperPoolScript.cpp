#include <crepe/api/Camera.h>

#include "../Config.h"
#include "../Random.h"

#include "ZapperPoolScript.h"
#include "ZapperPoolSubScene.h"
#include "util/OptionalRef.h"

using namespace crepe;
using namespace std;

ZapperPoolScript::ZapperPoolScript(std::vector<ZapperObject> && pool) : pool(pool) {}

void ZapperPoolScript::init() {
	subscribe<CreateZapperEvent>([this](const CreateZapperEvent &) {
		this->spawn_random();
		return true;
	});

	camera_transform = get_components_by_name<Transform>(CAMERA_NAME).back();
	camera_camera = get_components_by_name<Camera>(CAMERA_NAME).back();
}

void ZapperPoolScript::fixed_update(crepe::duration_t) {
	float threshold = camera_transform->position.x - camera_camera->viewport_size.x / 2 - OFFSCREEN_MARGIN;
	for (ZapperObject & zapper : this->pool) {
		if (!zapper.active) continue;

		if (zapper.transform.position.x < threshold)
			zapper.set_active(false);
	}
}

void ZapperPoolScript::spawn_random() {
	OptionalRef<ZapperObject> zapper = this->get_next_zapper();
	if (!zapper) return; // pool exhausted
	
	bool horizontal = Random::b();
	vec2 pos;
	float rotation, length;
	pos.x = camera_transform->position.x + camera_camera->viewport_size.x / 2 + OFFSCREEN_MARGIN;

	if (horizontal) {
		rotation = 90;
		length = Random::f(400, 200);
		pos.y = Random::f(0.5, -0.5) * HALLWAY_HEIGHT;
		// align zapper to right edge of camera
		pos.x -= MAX_LENGTH - (length / 2);
	} else {
		rotation = 0;
		length = Random::f(200, 75);
		// ensure zapper doesn't crash into ceiling or floor
		pos.y = Random::f(0.5, -0.5) * (HALLWAY_HEIGHT - length);
		// align zapper to right edge of camera
		pos.x -= MAX_LENGTH;
	}

	zapper->place(pos, rotation, length);
	zapper->set_active(true);
}

OptionalRef<ZapperObject> ZapperPoolScript::get_next_zapper() {
	for (ZapperObject & zapper : this->pool) {
		if (zapper.active) continue;
		return zapper;
	}
	return {};
}

