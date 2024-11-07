#pragma once

#include <string>
#include <vector>

#include "Component.h"

namespace crepe {

class Metadata : public Component {
public:
	Metadata(uint32_t game_object_id, const std::string & name,
			 const std::string & tag);
	virtual int get_instances_max() const { return 1; }

public:
	std::string name;
	std::string tag;
	uint32_t parent = -1;
	std::vector<uint32_t> children;
};

} // namespace crepe
