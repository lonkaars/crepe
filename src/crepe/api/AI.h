#pragma once

#include "Component.h"
#include "types.h"

namespace crepe {

/**
 * \brief The AI component is used to control the movement of an entity using AI.
 *
 * The AI component can be used to control the movement of an entity. The AI component can be used
 * to implement different behaviors such as seeking, fleeing, arriving, and path following.
 */
class AI : public Component {
public:
	//! The different types of behaviors that can be used
	enum BehaviorTypeMask {
		SEEK = 0x00002,
		FLEE = 0x00004,
		ARRIVE = 0x00008,
		PATH_FOLLOW = 0x00010,
	};

public:
	/**
	 * \param id The id of the game object
	 * \param max_force The maximum force that can be applied to the entity
	 */
	AI(game_object_id_t id, float max_force);

	/**
	 * \brief Check if a behavior is on (aka activated)
	 *
	 * \param behavior The behavior to check
	 * \return true if the behavior is on, false otherwise
	 */
	bool on(BehaviorTypeMask behavior) const { return (flags & behavior); }
	//! Turn on the seek behavior
	void seek_on() { flags |= SEEK; }
	//! Turn off the seek behavior
	void seek_off() { flags &= ~SEEK; }
	//! Turn on the flee behavior
	void flee_on() { flags |= FLEE; }
	//! Turn off the flee behavior
	void flee_off() { flags &= ~FLEE; }
	//! Turn on the arrive behavior
	void arrive_on() { flags |= ARRIVE; }
	//! Turn off the arrive behavior
	void arrive_off() { flags &= ~ARRIVE; }
	//! Turn on the path follow behavior
	void path_follow_on() { flags |= PATH_FOLLOW; }
	//! Turn off the path follow behavior
	void path_follow_off() { flags &= ~PATH_FOLLOW; }

	/**
	 * \brief Add a path node (for the path following behavior)
	 *
	 * \note The path is not relative to the entity's position (it is an absolute path)
	 *
	 * \param node The path node to add
	 */
	void add_path_node(const vec2 & node) { path.push_back(node); }
	/**
	 * \brief Make a circle path (for the path following behavior)
	 *
	 * \note The path is not relative to the entity's position (it is an absolute path)
	 *
	 * \param radius The radius of the circle (in game units)
	 * \param center The center of the circle (in game units)
	 * \param start_angle The start angle of the circle (in radians)
	 * \param clockwise The direction of the circle
	 */
	void make_circle_path(float radius, const vec2 & center = {0, 0}, float start_angle = 0,
						  bool clockwise = true);
	/**
	 * \brief Make an oval path (for the path following behavior)
	 *
	 * \note The path is not relative to the entity's position (it is an absolute path)
	 *
	 * \param radius_x The x radius of the oval (in game units)
	 * \param radius_y The y radius of the oval (in game units)
	 * \param center The center of the oval (in game units)
	 * \param start_angle The start angle of the oval (in radians)
	 * \param clockwise The direction of the oval
	 * \param rotation The rotation of the oval (in radians)
	 */
	void make_oval_path(float radius_x, float radius_y, const vec2 & center = {0, 0},
						float start_angle = 0, bool clockwise = true, float rotation = 0);

public:
	//! The maximum force that can be applied to the entity (higher values will make the entity adjust faster)
	float max_force;

	//! The target to seek at
	vec2 seek_target;
	//! The target to arrive at
	vec2 arrive_target;
	//! The target to flee from
	vec2 flee_target;
	//! The distance at which the entity will start to flee from the target
	float square_flee_panic_distance = 200.0f * 200.0f;
	//! The deceleration rate for the arrive behavior (higher values will make the entity decelerate faster (less overshoot))
	float arrive_deceleration = 40.0f;
	//! The path to follow (for the path following behavior)
	std::vector<vec2> path;
	//! The distance from the path node at which the entity will move to the next node (automatically set by make_circle_path())
	float path_node_distance = 400.0f;
	//! Looping behavior for the path
	bool path_loop = true;

private:
	//! The flags for the behaviors
	int flags = 0;
	//! The current path index
	size_t path_index = 0;

	//! The AISystem is the only class that should access the flags and path_index variables
	friend class AISystem;

	//! The minimum amount of steps for the path following behavior
	static constexpr int MIN_STEP = 16;
	//! The radius to step size ratio for the path following behavior
	static constexpr float RADIUS_TO_STEP = 400.0f;
};

} // namespace crepe
