#pragma once

#include <cstdint>
#include <vector>
#include <functional>

namespace crepe {

//! GameObject ID
typedef uint32_t game_object_id_t;

//! vector of reference_wrapper
template <typename T>
using RefVector = std::vector<std::reference_wrapper<T>>;

}
