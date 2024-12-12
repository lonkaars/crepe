#include <crepe/api/Text.h>
#include <crepe/facade/Font.h>
#include <crepe/facade/SDLContext.h>
#include <crepe/facade/SDLFontContext.h>
#include <crepe/manager/Mediator.h>
#include <exception>
#include <iostream>
#include <memory>
using namespace crepe;
int main() {

	SDLFontContext font_facade;
	Mediator mediator;
	SDLContext sdl_context{mediator};
	try {
		// Correct way to create a unique pointer for Text
		std::unique_ptr<Text> label
			= std::make_unique<Text>(1, vec2(100, 100), vec2(0, 0), "test test", "OpenSymbol");
		std::unique_ptr<Asset> asset = font_facade.get_font_asset(label->font_family);
		std::cout << "path: " << asset->get_path() << std::endl;
		std::unique_ptr<Font> font = std::make_unique<Font>(*asset, mediator);
		// Get the TTF_Font from the Font object
		TTF_Font* ttf_font = font->get_font();

		// Check if the font is loaded properly
		if (ttf_font != nullptr) {
			std::cout << "Font successfully loaded!" << std::endl;
		} else {
			std::cout << "Failed to load font." << std::endl;
		}
	} catch (const std::exception & e) {
		std::cout << "Standard exception thrown: " << e.what() << std::endl;
	}

	return 0;
}
