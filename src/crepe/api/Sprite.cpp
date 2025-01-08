#include <cmath>

#include "../util/dbg.h"
#include "api/Asset.h"

#include "Component.h"
#include "Sprite.h"
#include "types.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, const Asset & texture, const Sprite::Data & data)
	: Component(id),
	  source(texture),
	  data(data) {

	dbg_trace();
}

Sprite::~Sprite() { dbg_trace(); }

unique_ptr<Component> Sprite::save() const { return unique_ptr<Component>(new Sprite(*this)); }

void Sprite::restore(const Component & snapshot) {
	*this = static_cast<const Sprite &>(snapshot);
}

Sprite & Sprite::operator=(const Sprite & snapshot) {
	this->active = snapshot.active;
	this->data = snapshot.data;
	this->mask = snapshot.mask;
	return *this;
}
