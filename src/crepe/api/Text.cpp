#include "../types.h"

#include "Text.h"

using namespace crepe;
using namespace std;

Text::Text(
	game_object_id_t id, const vec2 & dimensions, const std::string & font_family,
	const Data & data, const vec2 & offset, const std::string & text
)
	: UIObject(id, dimensions, offset),
	  text(text),
	  data(data),
	  font_family(font_family) {}

unique_ptr<Component> Text::save() const { return unique_ptr<Component>(new Text(*this)); }

void Text::restore(const Component & snapshot) { *this = static_cast<const Text &>(snapshot); }

Text & Text::operator=(const Text & snapshot) {
	this->active = snapshot.active;
	this->data = snapshot.data;
	this->text = snapshot.text;
	this->font_family = snapshot.font_family;
	return *this;
}
