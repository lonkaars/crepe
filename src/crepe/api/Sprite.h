#pragma once

#include <SDL2/SDL_rect.h>
#include <cstdint>
#include <memory>

#include "api/Color.h"
#include "api/Texture.h"

#include "Component.h"

namespace crepe {

struct FlipSettings {
	bool flip_x = true;
	bool flip_y = true;
};

class Sprite : public Component {

public:
	Sprite(game_object_id_t id, std::shared_ptr<Texture> image,
		   const Color & color, const FlipSettings & flip);
	~Sprite();
	std::shared_ptr<Texture> sprite_image;
	Color color;
	FlipSettings flip;
	uint8_t sorting_in_layer;
	uint8_t order_in_layer;
};

} // namespace crepe
