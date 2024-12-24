#pragma once

#include <optional>
#include <string>

#include "../types.h"

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
		//! variable indicating if transform is relative to camera(false) or world(true)
		bool world_space = false;

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
		game_object_id_t id, const vec2 & dimensions, const std::string & font_family,
		const Data & data, const vec2 & offset = {0, 0}, const std::string & text = ""
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
