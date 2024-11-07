#include "Metadata.h"

using namespace crepe;
using namespace std;

Metadata::Metadata(uint32_t game_object_id, const string & name,
				   const string & tag)
	: Component(game_object_id), NAME(name), TAG(tag) {}
