#pragma once

#include "Component.h"
#include "api/Color.h"
#include "facade/Texture.h"
#include <cstdint>


namespace crepe::api {

struct flip_settings{
	bool flipX : 1;
	bool flipY : 1;
};
class Sprite : public Component {
	
public:
	Sprite(crepe::Texture& image, const Color& color, const flip_settings& flip ) :  sprite_image(&image), color(color), flip(flip){}
	crepe::Texture* sprite_image;
	Color color;
	flip_settings flip;
	uint8_t sortingLayer;
	uint8_t orderInLayer;


};

}
