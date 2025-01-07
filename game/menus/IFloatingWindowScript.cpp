#include "IFloatingWindowScript.h"

#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;

void IFloatingWindowScript::init(){
 this->disable_all_sprites();
}

void IFloatingWindowScript::disable_all_sprites(){
	RefVector<Sprite> sprites = this->get_components_by_tag<Sprite>(this->tag);
	for(Sprite & sprite : sprites){
		sprite.active = false;
	}
}

void IFloatingWindowScript::enable_all_sprites(){
	RefVector<Sprite> sprites = this->get_components_by_tag<Sprite>(this->tag);
	for(Sprite & sprite : sprites){
		sprite.active = true;
	}
}
