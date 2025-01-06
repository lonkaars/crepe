#pragma once

#include <crepe/types.h>
#include <crepe/api/GameObject.h>

namespace crepe {
class Scene;
}

class BannerSubScene {
public:
struct Data{
		const std::string & banner_title = "NODATA";
		const float banner_title_width = 100;
		const crepe::vec2 & banner_title_offset = {0,0};
	};
public:
	void create(crepe::Scene & scn,const Data & data);
};
