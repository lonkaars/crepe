#include "Metadata.h"

using namespace crepe;
using namespace std;

Metadata::Metadata(uint32_t gameObjectId, string name, string tag)
	: Component(gameObjectId), name(name), tag(tag) {}

int Metadata::get_instances_max() const { return 1; }
