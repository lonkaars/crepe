#pragma once

#include <crepe/api/Scene.h>
#include <crepe/types.h>

class FloatingWindowSubScene {
public:
	struct Data {
		const std::string group_tag = "";
		float width = 200;
		crepe::vec2 offset = {0, 0};
		float width_middle_offset = 0;
	};

public:
	void create(crepe::Scene & scn, const Data & data);
};
