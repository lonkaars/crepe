#include "../facade/FontFacade.h"
#include "util/Log.h"

#include "Text.h"

using namespace crepe;

Text::Text(game_object_id_t id, const vec2 & dimensions, const vec2 & offset,
		   const std::string & text, const std::string & font_family, const Data & data)
	: UIObject(id, dimensions, offset),
	  text(text),
	  data(data),
	  font(FontFacade::get_font_asset(font_family)) {
	dbg_trace();
}
