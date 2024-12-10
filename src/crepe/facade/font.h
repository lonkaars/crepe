#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>

#include "../api/Asset.h"

namespace crepe {

/**
 * \brief Font resource facade
 *
 * This class is a wrapper around an SDL_ttf font instance, encapsulating font loading and usage.
 */
class Font {
public:
    /**
     * \param src The file path to the font file.
     */
    Font(const char* src);

    /**
     * \param res A unique pointer to an Asset holding the font resource.
     */
    Font(std::unique_ptr<Asset> res);

    /**
     * \brief Destructor to clean up font resources.
     */
    ~Font() = default;

	void draw(const vec2& pos, const vec2&)
private:
    /**
     * \brief Load the font from the given resource.
     * 
     * This method is used by both constructors to load the font resource.
     * 
     * \param res A unique pointer to an Asset holding the font resource.
     */
    void load(std::unique_ptr<Asset> res);

private:
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;  ///< The SDL_ttf font object with custom deleter.
};

} // namespace crepe
