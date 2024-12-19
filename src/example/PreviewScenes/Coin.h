#pragma once

#include "api/AudioSource.h"
#include "api/GameObject.h"
#include "api/Sprite.h"
#include "util/OptionalRef.h"

class Coin {
public:
	Coin(crepe::GameObject & s, const crepe::vec2 & start_pos);
	
	void pickup();

private:
	crepe::OptionalRef<crepe::Sprite> coin_sprite;
	crepe::OptionalRef<crepe::AudioSource> coin_pickup_audio;
};
