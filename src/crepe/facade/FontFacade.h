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
	FontFacade();
	~FontFacade();
    FontFacade(const FontFacade & other) = delete;
    FontFacade & operator=(const FontFacade & other) = delete;
    FontFacade(FontFacade && other) noexcept = delete;
    FontFacade & operator=(FontFacade && other) noexcept = delete;
	/**
	 * 
	 * \brief Facade function to convert a font_family into an asset.
	 * 
	 * This function uses the FontConfig library to convert a font family name (Arial, Inter, Helvetica) and converts it to the font source path.
	 * This function returns a default font path if the font_family name doesnt exist or cant be found
	 * \param font_family Name of the font family name.
	 * \return Asset with filepath to the corresponding font.
	 */
	Asset get_font_asset(const std::string& font_family);
};

} // namespace crepe
