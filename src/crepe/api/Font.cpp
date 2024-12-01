#include <SDL2/SDL_ttf.h>

#include "facade/SDLContext.h"
#include "util/Log.h"

#include "Asset.h"
#include "Font.h"

using namespace crepe;
using namespace std;

Font::Font(const Asset &src, int size) : font_size(size) {
    dbg_trace();
    this->load(src, size);
}

Font::~Font() {
    dbg_trace();
    this->font.reset();
}

void Font::load(const Asset &res, int size) {
    SDLContext &ctx = SDLContext::get_instance();
    // Open the font using SDL's TTF_OpenFontRW, which supports loading from memory
    SDL_RWops *rw_ops = SDL_RWFromFile(res.get_path().c_str(), "rb");
    if (!rw_ops) {
        // dbg_log("Failed to create RWops for font: %s", SDL_GetError());
        return;
    }

    TTF_Font *loaded_font = TTF_OpenFontRW(rw_ops, 1, size); // 1 indicates SDL should free the RWops
    if (!loaded_font) {
        // dbg_log("Failed to load font from asset: %s", TTF_GetError());
        return;
    }

    // Wrap the TTF_Font with a unique_ptr for automatic cleanup
    this->font = unique_ptr<TTF_Font, function<void(TTF_Font *)>>(loaded_font, [](TTF_Font *f) {
        if (f) TTF_CloseFont(f);
    });
}

int Font::get_size() const {
    return this->font_size;
}
