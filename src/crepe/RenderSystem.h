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
};
} // namespace crepe
