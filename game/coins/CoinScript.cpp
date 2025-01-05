#include "CoinScript.h"
#include "api/CircleCollider.h"
#include "api/Sprite.h"
#include "manager/SaveManager.h"
#include "../Config.h"

using namespace crepe;
using namespace std;

bool CoinScript::on_collision(const CollisionEvent & collisionData){
	if(collisionData.info.other.metadata.name != PLAYER_NAME) return true;
	//collide with player
	this->get_component<Sprite>().active = false;
	this->get_component<CircleCollider>().active = false;
	SaveManager & savemgr = this->get_save_manager();
	int amount = savemgr.get<int>(TOTAL_COINS_RUN,0).get() + 1;
	savemgr.set(TOTAL_COINS_RUN, amount);
	return true;
}

void CoinScript::init(){
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool { return this->on_collision(ev); });
}

