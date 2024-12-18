#pragma once

#include "api/AudioSource.h"
#include "api/Sprite.h"
#include "example/PreviewScenes/Scene1.h"
#include "util/OptionalRef.h"

class Coin {
public:
	Coin(Scene1 & s, const crepe::vec2 & start_pos);
	
	void pickup();

private:
	Scene1 & scene;
	crepe::OptionalRef<crepe::Sprite> coin_sprite;
	crepe::OptionalRef<crepe::AudioSource> coin_pickup_audio;
};
