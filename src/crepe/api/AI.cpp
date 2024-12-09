#include "AI.h"

namespace crepe {

AI::AI(game_object_id_t id, float max_force) : Component(id), max_force(max_force) {}

void AI::make_circle_path(float radius, vec2 center, float start_angle, bool clockwise) {
	// The step size is determined by the radius (step size is in radians)
	float step = 400.0f / radius;
	// Force at least 16 steps (in case of a small radius)
	if (step > 2 * M_PI / 16) {
		step = 2 * M_PI / 16;
	}
	// The path node distance is determined by the step size and the radius
	path_node_distance = radius * step * 0.75f;

	if (clockwise) {
		for (float i = start_angle; i < 2 * M_PI + start_angle; i += step) {
			path.push_back(vec2{static_cast<float>(center.x + radius * cos(i)),
								static_cast<float>(center.y + radius * sin(i))});
		}
	} else {
		for (float i = start_angle; i > start_angle - 2 * M_PI; i -= step) {
			path.push_back(vec2{static_cast<float>(center.x + radius * cos(i)),
								static_cast<float>(center.y + radius * sin(i))});
		}
	}
}

} // namespace crepe
