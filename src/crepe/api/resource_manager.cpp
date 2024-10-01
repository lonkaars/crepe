

#include "resource_manager.h"
#include <string>
#include <unordered_map>

using namespace crepe::api;

ResourceManager& ResourceManager::get_instance(){
	static ResourceManager instance;
	return instance;
}


ResourceManager::~ResourceManager(){
	m_resources.clear();
}


void ResourceManager::Unload(const std::string& file_path){
	if(m_resources.find(file_path) != m_resources.end()){
		m_resources.erase(file_path);
	}
}

