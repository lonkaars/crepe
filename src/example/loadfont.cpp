#include <iostream>
#include <exception>
#include <memory>
#include <crepe/facade/SDLFontContext.h>
#include <crepe/api/Text.h>
#include <crepe/facade/Font.h>
#include <crepe/manager/Mediator.h>
using namespace crepe;

int main() {
    SDLFontContext font_facade;
	Mediator mediator;
	try{
		  // Correct way to create a unique pointer for Text
    std::unique_ptr<Text> label = std::make_unique<Text>(1, vec2(100, 100), vec2(0, 0), "test test","OpenSymbol");
	std::unique_ptr<Asset> asset = font_facade.get_font_asset(label->font_family);
	std::cout << "path: " << asset->get_path() << std::endl;
	std::unique_ptr<Font> font = make_unique<Font>(asset,mediator)
	}catch (const std::exception& e) {
    std::cout << "Standard exception thrown: " << e.what() << std::endl;
	}
  

    return 0;
}
