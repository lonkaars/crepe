#pragma once

#include <cstdint>
#include <memory>

#include "api/Color.h"
#include "api/Texture.h"

#include "Component.h"

namespace crepe {

struct FlipSettings {
	bool flip_x = 1;
	bool flip_y = 1;
};

class Sprite : public Component {

public:
	Sprite(uint32_t game_id, std::shared_ptr<Texture> image,
		   const Color & color, const FlipSettings & flip);
	~Sprite();
	std::shared_ptr<Texture> sprite_image;
	Color color;
	FlipSettings flip;
	uint8_t sorting_in_layer;
	uint8_t order_in_layer;

public:
	virtual int get_instances_max() const { return 10; }

private:
	friend class AnimatorSystem;
	friend class SDLContext;
	friend class Animator;
	struct Rect{
		int w = 0;
		int h = 0;
		int x = 0;
		int y = 0;
	};
	Rect sprite_rect;
	
};

} // namespace crepe
