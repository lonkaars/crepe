#pragma once



#include "api/Resource.h"
#include <memory>
#include <string>




class ResourceFactory {

public:

	template<typename T>
	static std::unique_ptr<crepe::api::Resource> create_resource(const std::string& file_path){
	
		return std::make_unique<T>(convert_file_to_string(file_path));
	}

private:
	static std::string convert_file_to_string(const std::string& path);

};




