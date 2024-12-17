#include "../facade/FontFacade.h"

#include "Text.h"

using namespace crepe;

Text::Text(game_object_id_t id, const vec2 & dimensions, const vec2 & offset,
		   const std::string & font_family, const Data & data, const std::string & text,
		   std::optional<Asset> font)
	: UIObject(id, dimensions, offset),
	  text(text),
	  data(data),
	  font_family(font_family),
	  font(font) {}
