#pragma once



#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "api/baseResource.h"


namespace crepe::api{

class ResourceManager{


private:
	
	std::unordered_map< std::string, std::unique_ptr<BaseResource>>  m_resources;


protected:
	ResourceManager() = default;
	~ResourceManager();

public:
	ResourceManager(const ResourceManager &) = delete;
	ResourceManager(ResourceManager &&) = delete;
	ResourceManager &operator=(const ResourceManager &) = delete;
	ResourceManager &operator=(ResourceManager &&) = delete;

	static ResourceManager& get_instance();



public:
	template<typename T>
	T* Load(const std::string& file_path){
		
		if (m_resources.find(file_path) != m_resources.end()) {
			return static_cast<T*>(m_resources[file_path].get());
		}

		auto resource = std::make_unique<T>(file_path.c_str());
		if (resource) {
			m_resources[file_path] = std::move(resource);
			return static_cast<T*>(m_resources[file_path].get() );
		}

		return nullptr;
	}

	void Unload(const std::string& file_path);

};
}
