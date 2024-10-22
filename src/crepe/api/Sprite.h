#pragma once

#include "Component.h"
#include "api/Color.h"
#include "api/Texture.h"
#include <SDL2/SDL_rect.h>
#include <cstdint>
#include <memory>


namespace crepe::api {

struct flip_settings{
	bool flip_x: 1;
	bool flip_y : 1;
};
class Sprite : public Component {
	
public:
	Sprite(std::unique_ptr<Texture> image, const Color& color, const flip_settings& flip );
	~Sprite();
	std::unique_ptr<Texture> sprite_image;
	Color color;
	flip_settings flip;
	uint8_t sorting_in_layer;
	uint8_t order_in_layer;

};

}
