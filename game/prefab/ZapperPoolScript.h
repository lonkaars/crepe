#pragma once

#include <crepe/api/Script.h>

#include "ZapperObject.h"
#include "util/OptionalRef.h"

class ZapperPoolSubScene;

class ZapperPoolScript : public crepe::Script {
public:
	ZapperPoolScript(std::vector<ZapperObject> && pool);

	void init();
	void fixed_update(crepe::duration_t);

	unsigned i = 0;

private:
	std::vector<ZapperObject> pool;

private:
	crepe::OptionalRef<crepe::Transform> camera_transform;
	crepe::OptionalRef<crepe::Camera> camera_camera;
	crepe::OptionalRef<ZapperObject> get_next_zapper();

private:
	void spawn_random();

private:
	static constexpr float OFFSCREEN_MARGIN = 40;
};

