#pragma once

#include <memory>

#include "../api/Asset.h"

namespace crepe {

/**
 * 
 * \brief Font facade class for converting font family names to absolute file paths
 * 
 */
class FontFacade {
public:
	/**
	 * 
	 * \brief Facade function to convert a font_family into an asset.
	 * 
	 * This function uses the FontConfig library to convert a font family name (Arial, Inter, Helvetica) and converts it to the font source path.
	 * This function is static so the member function can be used without create a FontFacade object. This way it can be used in a constructor as FontFacade::get_font_asset().
	 * \param font_family Name of the font family name.
	 * \return Asset with filepath to the font.
	 */
	 static Asset get_font_asset(const std::string font_family);
};

} // namespace crepe
