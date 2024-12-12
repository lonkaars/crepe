#include "Text.h"

using namespace crepe;

Text::Text(game_object_id_t id, const vec2 & dimensions, const vec2 & offset, const std::string & text,
		   const std::string & font_family)
	: UIObject(id, dimensions, offset),
	  text(text),
	  font_family(font_family) {}
