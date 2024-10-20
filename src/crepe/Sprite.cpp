#include <string>

#include "Sprite.h"

using namespace crepe;
using namespace std;

Sprite::Sprite(uint32_t gameObjectId, string path) : Component(gameObjectId), path(path) {}
