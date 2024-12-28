#include "CoinSystemScript.h"
#include "CoinSystem.h"
#include "api/CircleCollider.h"
#include "api/Metadata.h"
#include "api/Transform.h"

using namespace crepe;
using namespace std;

void CoinSystemScript::frame_update(crepe::duration_t dt)
{
	float position = this->get_component<Transform>().position.x;
	RefVector<Sprite> coin_sprites = this->get_components_by_tag<Sprite>("coin");
	RefVector<CircleCollider> coin_colliders = this->get_components_by_tag<CircleCollider>("coin");
	RefVector<Metadata> coin_metadatas = this->get_components_by_tag<Metadata>("coin");
	this->coin_system.update(position, coin_sprites, coin_colliders, coin_metadatas);	
}

