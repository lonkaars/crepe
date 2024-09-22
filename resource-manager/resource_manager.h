#pragma once



#include <algorithm>
#include <string>
#include <unordered_map>


#include "resource.h"
#include "constants.h"
#include "resource_fabricator.h"

using namespace crepe;



class ResourceManager{

public:

	ResourceManager();
	~ResourceManager();
	
	template<typename T>
	T* Load(const Constants::FILE_PATH& file_path){
		
		if (m_resources.find(file_path) != m_resources.end()) {
			return static_cast<T*>(m_resources[file_path]);
		}

		Resource* resource = ResourceFactory::create_resource(file_path);
		if (resource) {
			m_resources[file_path] = std::move(resource);
		}
		return static_cast<T*>(m_resources[file_path]);
	}

	void Unload(const Constants::FILE_PATH& file_path);

private:
	std::unordered_map<Constants::FILE_PATH, Resource*> m_resources;



};
