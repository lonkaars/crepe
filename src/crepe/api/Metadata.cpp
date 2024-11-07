#include "Metadata.h"

using namespace crepe;
using namespace std;

Metadata::Metadata(game_object_id_t id, const string & name, const string & tag)
	: Component(id), name(name), tag(tag) {}
