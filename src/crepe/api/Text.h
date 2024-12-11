#pragma once

#include <string>

#include "../Component.h"

#include "Asset.h"
#include "Color.h"
#include "UIObject.h"

namespace crepe{
class Text : public UIObject{
public:
	Text(game_object_id_t id,const vec2 & dimensions, const vec2 & offset, const Asset & font, int font_size);

	//! Label text.
	std::string text;
	//! Label text color
	Color text_color = Color::BLACK;
	/**
	 *  \brief fontsize for text rendering
	 * 
	 * \note this is not the actual font size that is loaded in.
	 * 
	 * Since SDL_TTF requires the font size when loading in the font it is not possible to switch the font size.
	 * The default font size that is loaded is set in the Config.
	 * Instead this value is used to upscale the font texture which can cause blurring or distorted text when upscaling or downscaling too much.
	 */
	int font_size = 16;

	const Asset source;
private:
};

} // namespace crepe
