

#include "Image_asset.h"
#include <SDL_image.h>
#include <SDL_surface.h>
#include <string>

Texture::Texture(const std::string & content) { this->m_content = content; }

Texture::~Texture() {}
