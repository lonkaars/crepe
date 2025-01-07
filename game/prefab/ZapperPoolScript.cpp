#include <crepe/api/Camera.h>

#include "../Config.h"

#include "ZapperPoolScript.h"
#include "ZapperPoolSubScene.h"

using namespace crepe;
using namespace std;

ZapperPoolScript::ZapperPoolScript(ZapperPoolSubScene & pool) : pool(pool) {}

void ZapperPoolScript::init() {
	subscribe<CreateZapperEvent>([this](const CreateZapperEvent &) {
		this->spawn_random();
		return true;
	});
}

void ZapperPoolScript::fixed_update(crepe::duration_t) {
	if (i++ < 80) return;
	i = 0;
	queue_event<CreateZapperEvent>();
}

void ZapperPoolScript::spawn_random() {
	vec2 pos = this->get_camera_pos();
	logf(Log::DEBUG, "Spawning random zapper at {}", pos);

}

vec2 ZapperPoolScript::get_camera_pos() {
	Transform & transform = get_components_by_name<Transform>(CAMERA_NAME).back();
	Camera & camera = get_components_by_name<Camera>(CAMERA_NAME).back();

	// right middle edge position
	return transform.position + vec2(camera.viewport_size.x / 2, 0);
}

