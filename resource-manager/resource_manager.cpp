

#include "resource_manager.h"
#include "constants.h"
#include "resource.h"
#include "resource_fabricator.h"
#include <SDL2/SDL_image.h>
#include <unordered_map>


ResourceManager::ResourceManager(){
	IMG_Init(IMG_INIT_PNG);
}

ResourceManager::~ResourceManager(){

	for(auto pair : m_resources){
		delete pair.second;
	}

	m_resources.clear();

	IMG_Quit();
}


Resource* ResourceManager::Load(const Constants::FILE_PATH& file_path){

	if(m_resources.find(file_path) != m_resources.end(	)){
		return m_resources[file_path];
	}

	Resource* res = ResourceFactory::create_resource(file_path);
	if(res){
		m_resources[file_path] = std::move(res);
	}

	return m_resources[file_path];
}


void ResourceManager::Unload(const Constants::FILE_PATH& file_path){
	std::unordered_map<Constants::FILE_PATH, Resource* >::iterator itr = m_resources.find(file_path);
	if(itr != m_resources.end()){
		delete itr->second;
		m_resources.erase(itr);
	}
}
