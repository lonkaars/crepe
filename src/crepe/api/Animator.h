#pragma once

#include "Component.h"
#include "Sprite.h"

namespace crepe {

class AnimatorSystem;
class SDLContext;

/**
 * \brief The Animator component is used to animate sprites by managing the movement and frame
 * changes within a sprite sheet.
 *
 * This component allows for controlling sprite animation through rows and columns of a sprite
 * sheet. It can be used to play animations, loop them, or stop them.
 */
class Animator : public Component {

public:
	/**
	 * \brief Constructs an Animator object that will control animations for a sprite sheet.
	 *
	 * \param id The unique identifier for the component, typically assigned automatically.
	 * \param spritesheet A reference to the Sprite object which holds the sprite sheet for
	 * animation.
	 * \param row The maximum number of rows in the sprite sheet.
	 * \param col The maximum number of columns in the sprite sheet.
	 * \param col_animate The specific col index of the sprite sheet to animate. This allows
	 * selecting which col to animate from multiple col in the sheet.
	 *
	 * This constructor sets up the Animator with the given parameters, and initializes the
	 * animation system.
	 */
	Animator(uint32_t id, Sprite & spritesheet, int row, int col, int col_animate);

	~Animator(); // dbg_trace

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

	//! should the animation loop
	bool looping = false;

	//! starting frame for cycling
	int cycle_start = 0;

	//! end frame for cycling (-1 --> use last frame)
	int cycle_end = -1;

	//! frames per second for animation
	int fps = 1;

	int offset_x = 0;

public:
	void loop() { this->looping = true; }
	void play() {this->active = true;}
	void pause() {this->active = false;}
	void stop() {this->active = false; this->curr_col = 0; this->curr_row = 0;}
	void set_fps(int fps) {this->fps = fps;}
	void set_cycle_range(int start, int end) {this->cycle_start = start, this->cycle_end = end;}
	void set_anim(int col) {this->curr_row = 0; this->curr_col = col; }

private:
	//! AnimatorSystem adjust the private member parameters of Animator;
	friend class AnimatorSystem;
};
} // namespace crepe
//
