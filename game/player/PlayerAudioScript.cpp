#include "PlayerAudioScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>

using namespace crepe;
using namespace std;

void PlayerAudioScript::fixed_update(crepe::duration_t dt) {
	Animator & animator = this->get_components_by_name<Animator>("player").front();

	if (animator.data.col == 0) {
		if (animator.data.row != this->last_row) {
			if (animator.data.row == 0) {
				// right footstep
				if (current_footstep == 0) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(0);
					audio.play();
				} else if (current_footstep == 1) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(2);
					audio.play();
				} else if (current_footstep == 2) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(4);
					audio.play();
				} else if (current_footstep == 3) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(6);
					audio.play();
				}
			} else if (animator.data.row == 2) {
				// left footstep
				if (current_footstep == 0) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(1);
					audio.play();
					current_footstep = 1;
				} else if (current_footstep == 1) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(3);
					audio.play();
					current_footstep = 2;
				} else if (current_footstep == 2) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(5);
					audio.play();
					current_footstep = 3;
				} else if (current_footstep == 3) {
					AudioSource & audio
						= this->get_components_by_name<AudioSource>("player_audio").at(7);
					audio.play();
					current_footstep = 0;
				}
			}
			this->last_row = animator.data.row;
		}
	} else {
		this->last_row = -1;
	}
}
