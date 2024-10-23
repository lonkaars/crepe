#pragma once

#include "Component.h"

namespace crepe {

struct Position
{
	int x;
	int y;
};


class Transform : public Component {
public:
	Transform(uint32_t gameObjectId,Position position, int rotation, int scale);
	Position postion;
	int rotation;
	int scale;
};

} // namespace crepe
