#include "Text.h"

using namespace crepe;

Text::Text(game_object_id_t id,const vec2 & dimensions, const vec2 & offset, const Asset & font) : UIObject(id,dimensions,offset),source(font){}

