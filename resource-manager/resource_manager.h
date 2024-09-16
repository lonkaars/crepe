#pragma once



#include <string>
#include <unordered_map>


#include "resource.h"
#include "constants.h"

using namespace crepe;



class ResourceManager{

public:

	ResourceManager();
	~ResourceManager();
	
	Resource* Load(const Constants::FILE_PATH& file_path);
	void Unload(const Constants::FILE_PATH& file_path);


private:
	std::unordered_map<Constants::FILE_PATH, Resource*> m_resources;



};
