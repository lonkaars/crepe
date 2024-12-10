#pragma once

#include "Asset.h"
#include "../Component.h"
class Text : public Component{
public:
	Text(game_object_id_t id, const Asset & font, int font_size);

	int font_size = 16;
	const Asset source;
private:
};
