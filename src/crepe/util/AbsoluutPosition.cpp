#include "AbsoluutPosition.h"

using namespace crepe;

vec2 AbsoluutPosition::get_position(const Transform & transform,const vec2 & offset) {
	// Get the rotation in radians
	float radians1 = transform.rotation * (M_PI / 180.0);

	// Calculate total offset with scale
	vec2 total_offset = offset * transform.scale;

	// Rotate
	float rotated_total_offset_x1
		= total_offset.x * cos(radians1) - total_offset.y * sin(radians1);
	float rotated_total_offset_y1
		= total_offset.x * sin(radians1) + total_offset.y * cos(radians1);

	// Final positions considering scaling and rotation
	return (transform.position + vec2(rotated_total_offset_x1, rotated_total_offset_y1));
}

