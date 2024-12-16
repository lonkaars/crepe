#include <crepe/api/Text.h>
#include <crepe/facade/Font.h>
#include <crepe/facade/SDLContext.h>
#include <crepe/manager/Mediator.h>
#include <exception>
#include <iostream>
#include <memory>
using namespace crepe;
int main() {

	// SDLFontContext font_facade;
	Mediator mediator;
	SDLContext sdl_context{mediator};
	try {
		// Correct way to create a unique pointer for Text
		std::unique_ptr<Text> label = std::make_unique<Text>(
			1, vec2(100, 100), vec2(0, 0), "test test", "OpenSymbol", Text::Data{});
		std::cout << "Path: " << label->font.get_path() << std::endl;

		std::unique_ptr<Text> label2
			= std::make_unique<Text>(1, vec2(100, 100), vec2(0, 0), "test test",
									 "fsaafdafsdafsdafsdasfdds", Text::Data{});
		std::cout << "Path: " << label2->font.get_path() << std::endl;
	} catch (const std::exception & e) {
		std::cout << "Standard exception thrown: " << e.what() << std::endl;
	}

	return 0;
}
