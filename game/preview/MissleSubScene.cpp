#include "MissleSubScene.h"

#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
using namespace crepe;

MissleSubScene::MissleSubScene(Scene & scn){

	GameObject missle = scn.new_object("missle", "TAG", vec2 {0, 0}, 0, 1);

}
