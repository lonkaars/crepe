#pragma once

#include "../types.h"

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
	struct Data {
		//! frames per second for animation
		unsigned int fps = 1;
		//! The current col being animated.
		unsigned int col = 0;
		//! The current row being animated.
		unsigned int row = 0;
		//! should the animation loop
		bool looping = false;
		//! starting frame for cycling
		unsigned int cycle_start = 0;
		//! end frame for cycling (-1 = use last frame)
		int cycle_end = -1;
	};

public:
	//! Animator will repeat the animation
	void loop();
	//! starts the animation
	void play();
	//! pauses the animation
	void pause();
	/**
	 * \brief stops the animation
	 *
	 * sets the active on false and resets all the current rows and columns
	 */
	void stop();
	/**
	 * \brief set frames per second
	 *
	 * \param fps frames per second
	 */
	void set_fps(int fps);
	/**
	 * \brief set the range in the row
	 *
	 * \param start of row animation
	 * \param end of row animation
	 */
	void set_cycle_range(int start, int end);
	/**
	 * \brief select which column to animate from
	 *
	 * \param col animation column
	 */
	void set_anim(int col);
	//! will go to the next animaiton of current row
	void next_anim();

public:
	/**
	 * \brief Constructs an Animator object that will control animations for a sprite sheet.
	 *
	 * \param id The unique identifier for the component, typically assigned automatically.
	 * \param spritesheet the reference to the spritesheet
	 * \param single_frame_size the width and height in pixels of a single frame inside the
	 * spritesheet
	 * \param grid_size the max rows and columns inside the given spritesheet
	 * \param data extra animation data for more control
	 *
	 * This constructor sets up the Animator with the given parameters, and initializes the
	 * animation system.
	 */
	Animator(
		game_object_id_t id, Sprite & spritesheet, const ivec2 & single_frame_size,
		const uvec2 & grid_size, const Animator::Data & data
	);
	~Animator(); // dbg_trace

public:
	Animator::Data data;

private:
	//! A reference to the Sprite sheet containing.
	Sprite & spritesheet;

	//! The maximum number of rows and columns inside the spritesheet
	const uvec2 grid_size;

	//! Uses the spritesheet
	friend AnimatorSystem;
};

} // namespace crepe
