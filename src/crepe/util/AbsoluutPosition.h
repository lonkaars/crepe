#pragma once


#include "api/Transform.h"

#include "types.h"

namespace crepe {


class AbsoluutPosition {
public:
	static vec2 get_position(const Transform & transform,const vec2 & offset);

};

} // namespace crepe
