#include "Transform.h"

using namespace crepe;

Transform::Transform(uint32_t gameObjectId,Position position, int rotation, int scale)
	: Component(gameObjectId), postion(postion), rotation(rotation), scale(scale) {}
