#pragma once

#include "Component.h"
#include "Sprite.h"

namespace crepe {

class AnimatorSystem;
class SDLContext;

/**
 * \brief The Animator component is used to animate sprites by managing the movement
 *        and frame changes within a sprite sheet.
 *
 * This component allows for controlling sprite animation through rows and columns of a sprite sheet.
 * It can be used to play animations, loop them, or stop them.
 */
class Animator : public Component {

public:
	//TODO: need to implement this
	void loop();
	void stop();

public:
	/**
	 * \brief Constructs an Animator object that will control animations for a sprite sheet.
	 *
	 * \param id The unique identifier for the component, typically assigned automatically.
	 * \param spritesheet A reference to the Sprite object which holds the sprite sheet for animation.
	 * \param row The maximum number of rows in the sprite sheet.
	 * \param col The maximum number of columns in the sprite sheet.
	 * \param col__animate The specific col index of the sprite sheet to animate. This allows selecting which col to animate from multiple col in the sheet.
	 *
	 * This constructor sets up the Animator with the given parameters, and initializes the animation system.
	 */
	Animator(game_object_id_t id, Sprite & spritesheet, int row, int col,
			 int col_animate);

	~Animator(); // dbg_trace
	Animator(const Animator &) = delete;
	Animator(Animator &&) = delete;
	Animator & operator=(const Animator &) = delete;
	Animator & operator=(Animator &&) = delete;

private:
	//! A reference to the Sprite sheet containing the animation frames.
	Sprite & spritesheet;

	//! The maximum number of columns in the sprite sheet.
	const int col;

	//! The maximum number of rows in the sprite sheet.
	const int row;

	//! The current col being animated.
	int curr_col = 0;

	//! The current row being animated.
	int curr_row = 0;

	Rect animator_rect;

	//TODO: Is this necessary?
	//int fps;

private:
	//! AnimatorSystem adjust the private member parameters of Animator;
	friend class AnimatorSystem;

	//! SDLContext reads the Animator member var's
	friend class SDLContext;
};
} // namespace crepe
//
