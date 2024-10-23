#include "Force.h"
#include <cmath>

namespace crepe {

Force::Force(uint32_t gameObjectId, uint32_t forceMagnitude, uint32_t direction): Component(gameObjectId)
{ 
	// Convert direction from degrees to radians
    float radian_direction = static_cast<float>(direction) * (M_PI / 180.0f);
    force_x = static_cast<int32_t>(std::round(forceMagnitude * std::cos(radian_direction)));
    force_y = static_cast<int32_t>(std::round(forceMagnitude * std::sin(radian_direction)));
}

} // namespace crepe
