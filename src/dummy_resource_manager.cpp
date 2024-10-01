



#include "api/Image_asset.h"
#include "api/resource_manager.h"
#include <iostream>
#include <ostream>



using namespace crepe;

int main(){

	// get instance of resource manager
	api::ResourceManager& c_ResMan = api::ResourceManager::get_instance();

	// make a resouce from the file path
	api::Texture* img = c_ResMan.Load<api::Texture>("../asset/texture/img.png");

	std::cout << img->getContent() << std::endl;
}
