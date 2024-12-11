#include "font.h"
#include "../api/Config.h"
using namespace std;
using namespace crepe;

void Font::load(unique_ptr<Asset> res){
	const char* font_path = res->get_path();
	int font_size = Config::get_instance().font.font_size;
    this->font = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(
        TTF_OpenFont(font_path, font_size), &TTF_CloseFont); 

    if (!font) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }
}
Font::Font(const char* src){
	this->load(make_unique<Asset>(src));
}
Font::Font(std::unique_ptr<Asset> res){
	this->load(std::move(res));
}
const TTF_Font& Font::get_font() const{
	return this->font;
}
