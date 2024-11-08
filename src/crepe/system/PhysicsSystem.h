#pragma once

namespace crepe {
/**
 * \brief System that controls all physics
 * 
 * This class is a physics system that uses a rigidbody and transform
 * to add physics to a game object.
 */
class PhysicsSystem {
public:
	/**
	 * Constructor is default
	 */
	PhysicsSystem() = default;
	/**
	 * \brief updates the physics system.
	 * 
	 * It calculates new velocties and changes the postion in the transform.
	 */
	void update();
};

} // namespace crepe
