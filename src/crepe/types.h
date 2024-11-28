#pragma once

#include "api/Vector2.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace crepe {

//! GameObject ID
typedef uint32_t game_object_id_t;

//! vector of reference_wrapper
template <typename T>
using RefVector = std::vector<std::reference_wrapper<T>>;

//! Default Vector2<int> type
typedef Vector2<int> ivec2;

//! Default Vector2<unsigned int> type
typedef Vector2<unsigned int> uvec2;

//! Default Vector2<float> type
typedef Vector2<float> vec2;

//! Default Vector2<double> type
typedef Vector2<double> dvec2;

}; // namespace crepe
