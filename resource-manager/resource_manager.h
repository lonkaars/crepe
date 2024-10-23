#pragma once



#include <SDL_render.h>
#include <unordered_map>


#include "resource.h"
#include "constants.h"
#include "resource_fabricator.h"

using namespace crepe;

class ResourceManager{


private:
	
	static ResourceManager* m_single_resource_manager;
	std::unordered_map<Constants::FILE_PATH, Resource*> m_resources;



protected:
	ResourceManager();
	~ResourceManager();

public:
	ResourceManager(const ResourceManager &) = delete;
	ResourceManager(ResourceManager &&) = delete;
	ResourceManager &operator=(const ResourceManager &) = delete;
	ResourceManager &operator=(ResourceManager &&) = delete;

	static ResourceManager* get_instance();



public:
	template<typename T>
	T* Load(const Constants::FILE_PATH& file_path){
		
		if (m_resources.find(file_path) != m_resources.end()) {
			return static_cast<T*>(m_resources[file_path]);
		}

		Resource* resource = ResourceFactory::create_resource<T>(file_path);
		if (resource) {
			m_resources[file_path] = std::move(resource);
		}
		return static_cast<T*>(m_resources[file_path]);
	}

	void Unload(const Constants::FILE_PATH& file_path);



};
