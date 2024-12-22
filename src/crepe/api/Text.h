#pragma once

#include <optional>
#include <string>

#include "Asset.h"
#include "Color.h"
#include "UIObject.h"

namespace crepe {
/**
 * \brief Text UIObject component for displaying text
 * 
 * This class can be used to display text on screen. By setting the font_family to a font already stored on the current device it will automatically be loaded in.
 */
class Text : public UIObject {
public:
	//! Text data that does not have to be set in the constructor
	struct Data {
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

		//! Label text color.
		Color text_color = Color::BLACK;
	};

public:
	/**
	 * 
	 * \param dimensions Width and height of the UIObject.
	 * \param offset Offset of the UIObject relative to its transform
	 * \param text The text to be displayed.
	 * \param font_family The font style name to be displayed.
	 * \param data Data struct containing extra text parameters.
	 * \param font Optional font asset that can be passed or left empty.
	 */
	Text(
		game_object_id_t id, const vec2 & dimensions, const vec2 & offset,
		const std::string & font_family, const Data & data, const std::string & text = ""
	);

	//! Label text.
	std::string text = "";
	//! font family name
	std::string font_family = "";
	//! Font asset variable if this is not set, it will use the font_family to create an asset.
	std::optional<Asset> font;
	//! Data instance
	Data data;
};

} // namespace crepe
