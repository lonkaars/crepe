#pragma once

#include <crepe/api/Script.h>

class ZapperPoolSubScene;

class ZapperPoolScript : public crepe::Script {
public:
	ZapperPoolScript(ZapperPoolSubScene & pool);

	void init();

private:
	ZapperPoolSubScene & pool;

private:
	crepe::vec2 get_camera_pos();

private:
	void spawn_random();
};

