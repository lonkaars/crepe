#include <iostream>
#include <memory>

#include <crepe/facade/SDLFontContext.h>

using namespace crepe;

int main(){
	SDLFontContext font_facade;
	std::unique_ptr<Asset> asset = font_facade.get_font_asset("OpenSymbol");
	std::cout << "path: " << asset->get_path() << std::endl;
	return 0;
}
