#pragma once

#include "Component.h"
#include <cstdint>
#include <utility>

namespace crepe {

class Force : public Component {
public:
    Force(uint32_t gameObjectId, uint32_t forceMagnitude, uint32_t direction);

    int32_t force_x;
    int32_t force_y;
};

} // namespace crepe
