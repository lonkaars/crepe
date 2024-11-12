#include "Metadata.h"

using namespace crepe;
using namespace std;

Metadata::Metadata(const Component::Data & data, const string & name, const string & tag)
	: Component(data),
	  name(name),
	  tag(tag) {}
