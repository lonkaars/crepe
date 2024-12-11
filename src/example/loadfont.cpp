#include <iostream>
#include <exception>
#include <memory>
#include <crepe/facade/SDLFontContext.h>
#include <crepe/api/Text.h>

using namespace crepe;

int main() {
    SDLFontContext font_facade;

    // Create a unique pointer to the font asset
    std::unique_ptr<Asset> asset = font_facade.get_font_asset("OpenSymbol");
    std::cout << "path: " << asset->get_path() << std::endl;
	try{
		  // Correct way to create a unique pointer for Text
    std::unique_ptr<Text> label = std::make_unique<Text>(1, vec2(100, 100), vec2(0, 0), *asset);
	}catch (const std::exception& e) {
    std::cout << "Standard exception thrown: " << e.what() << std::endl;
	}
  

    return 0;
}
