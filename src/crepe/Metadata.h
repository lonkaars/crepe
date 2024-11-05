#pragma once

#include <string>
#include <vector>

#include "Component.h"

namespace crepe {

class Metadata : public Component {
public:
	Metadata(uint32_t game_object_id, std::string name, std::string tag);
	int get_instances_max() const;

public:
	std::string name;
	std::string tag;
	uint32_t parent = UINT32_MAX;
	std::vector<uint32_t> children;
};

} // namespace crepe
