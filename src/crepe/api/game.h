#pragma once


#include "api/spritesheet.h"
#include "facade/Texture.h"
#include <vector>

class game {

public:
	game(){}
	~game(){}

	void render(std::vector<crepe::Texture*>&, std::vector<crepe::api::Spritesheet*>&);
};
