#include <stdexcept>

#include "AI.h"

namespace crepe {

AI::AI(game_object_id_t id, float max_force) : Component(id), max_force(max_force) {}

void AI::make_circle_path(float radius, const vec2 & center, float start_angle,
						  bool clockwise) {
	if (radius <= 0) {
		throw std::runtime_error("Radius must be greater than 0");
	}

	// The step size is determined by the radius (step size is in radians)
	float step = RADIUS_TO_STEP / radius;
	// Force at least MIN_STEP steps (in case of a small radius)
	if (step > 2 * M_PI / MIN_STEP) {
		step = 2 * M_PI / MIN_STEP;
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

void AI::make_oval_path(float radius_x, float radius_y, const vec2 & center, float start_angle,
						bool clockwise, float rotation) {
	if (radius_x <= 0 && radius_y <= 0) {
		throw std::runtime_error("Radius must be greater than 0");
	}

	float max_radius = std::max(radius_x, radius_y);
	// The step size is determined by the radius (step size is in radians)
	float step = RADIUS_TO_STEP / max_radius;
	// Force at least MIN_STEP steps (in case of a small radius)
	if (step > 2 * M_PI / MIN_STEP) {
		step = 2 * M_PI / MIN_STEP;
	}
	// The path node distance is determined by the step size and the radius
	path_node_distance = max_radius * step * 0.75f;

	auto rotate_point = [rotation](vec2 point, vec2 center) {
		float s = sin(rotation);
		float c = cos(rotation);

		// Translate point back to origin
		point.x -= center.x;
		point.y -= center.y;

		// Rotate point
		float xnew = point.x * c - point.y * s;
		float ynew = point.x * s + point.y * c;

		// Translate point back
		point.x = xnew + center.x;
		point.y = ynew + center.y;

		return point;
	};

	if (clockwise) {
		for (float i = start_angle; i < 2 * M_PI + start_angle; i += step) {
			vec2 point = {static_cast<float>(center.x + radius_x * cos(i)),
						  static_cast<float>(center.y + radius_y * sin(i))};
			path.push_back(rotate_point(point, center));
		}
	} else {
		for (float i = start_angle; i > start_angle - 2 * M_PI; i -= step) {
			vec2 point = {static_cast<float>(center.x + radius_x * cos(i)),
						  static_cast<float>(center.y + radius_y * sin(i))};
			path.push_back(rotate_point(point, center));
		}
	}
}

} // namespace crepe
