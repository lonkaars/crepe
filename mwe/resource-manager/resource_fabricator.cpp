

#include "resource_fabricator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>




std::string ResourceFactory::convert_file_to_string(const std::string& path){
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::ifstream::pos_type fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> bytes(fileSize);
    file.read(bytes.data(), fileSize);

    return std::string(bytes.begin(), bytes.end());
}
