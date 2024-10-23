

#include "resource_manager.h"
#include "constants.h"
#include "resource.h"
#include <unordered_map>

ResourceManager * ResourceManager::m_single_resource_manager = nullptr;

ResourceManager * ResourceManager::get_instance() {
	if (m_single_resource_manager == nullptr) {
		m_single_resource_manager = new ResourceManager();
	}
	return m_single_resource_manager;
}

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {

	for (auto pair : m_resources) {
		delete pair.second;
	}

	delete m_single_resource_manager;
}

void ResourceManager::Unload(const Constants::FILE_PATH & file_path) {
	std::unordered_map<Constants::FILE_PATH, Resource *>::iterator itr
		= m_resources.find(file_path);
	if (itr != m_resources.end()) {
		delete itr->second;
		m_resources.erase(itr);
	}
}
