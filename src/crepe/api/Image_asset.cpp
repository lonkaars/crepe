

#include "Image_asset.h"
#include <string>

using namespace crepe::api;

Texture::Texture(const std::string& content){
	this->m_content = content;
}


Texture::~Texture(){
}
