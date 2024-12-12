#pragma once

#include <string>

#include "../Component.h"

#include "Asset.h"
#include "Color.h"
#include "UIObject.h"

namespace crepe{

/**
 * \brief Text UIObject component for displaying text
 * 
 * This class can be used to display text on screen. By setting the font_family to a font already stored on the current device it will automatically be loaded in.
 */
class Text : public UIObject{
public:
	Text(game_object_id_t id,const vec2 & dimensions, const vec2 & offset,std::string text,std::string font_family);
	//! Text data that does not have to be set in the constructor
	struct Data {
		//! Label text color.
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
		unsigned int font_size = 16;
		//! Layer sorting level of the text
		const int sorting_in_layer = 0;

		//! Order within the sorting text
		const int order_in_layer = 0;
	};
public:
	//! font family name such as (Arial,Helvetica,Inter)
	std::string font_family = "";
	//! Label text.
	std::string text = "";
	// Data instance for data not gotten from constructor
	Data data;
};

} // namespace crepe
