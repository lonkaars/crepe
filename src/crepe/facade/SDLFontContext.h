#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>
#include <fontconfig/fontconfig.h>

#include "../api/Asset.h"

namespace crepe {
	class SDLFontContext{
	public:
		SDLFontContext();
		~SDLFontContext();
		std::unique_ptr<Asset> get_font_asset(const std::string & font_family);
	private:
	};

}
