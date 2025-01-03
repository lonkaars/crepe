#include "CoinScript.h"
#include "api/CircleCollider.h"
#include "api/Sprite.h"
#include "manager/SaveManager.h"

using namespace crepe;
using namespace std;

bool CoinScript::on_collision(const CollisionEvent & collisionData){
	if(collisionData.info.other.metadata.name != PLAYER_NAME) return true;
	//collide with player
	this->get_component<Sprite>().active = false;
	this->get_component<CircleCollider>().active = false;
	SaveManager & savemgr = this->get_save_manager();
	int amount = savemgr.get<int>(COIN_GAME_AMOUNT,0).get() + 1;
	savemgr.set(COIN_GAME_AMOUNT, amount);
	return true;
}

void CoinScript::init(){
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool { return this->on_collision(ev); });
}

