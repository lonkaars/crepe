#pragma once

#include "System.h"

namespace crepe {

class RenderSystem : public System {

public:
	static RenderSystem & get_instance();
	void update();

private:
	RenderSystem();
	~RenderSystem();

	void clear_screen();
	void present_screen();
	void update_camera();
	void render_sprites();
};
} // namespace crepe
