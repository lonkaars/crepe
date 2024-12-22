#include "Text.h"
#include "types.h"

using namespace crepe;

Text::Text(
	game_object_id_t id, const vec2 & dimensions, const std::string & font_family,
	const Data & data, const vec2 & offset, const std::string & text
)
	: UIObject(id, dimensions, offset),
	  text(text),
	  data(data),
	  font_family(font_family) {}
