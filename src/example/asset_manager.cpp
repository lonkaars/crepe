

#include <crepe/Sound.h>
#include <crepe/api/AssetManager.h>
#include <crepe/api/Texture.h>

using namespace crepe;
using namespace crepe::api;
int main() {

	// this needs to be called before the asset manager otherwise the destructor of sdl is not in the right order
	{ Texture test("../asset/texture/img.png"); }

	auto & mgr = AssetManager::get_instance();

	{
		auto bgm = mgr.cache<Sound>("../mwe/audio/bgm.ogg");
		auto sfx1 = mgr.cache<Sound>("../mwe/audio/sfx1.wav");
		auto sfx2 = mgr.cache<Sound>("../mwe/audio/sfx2.wav");

		auto img = mgr.cache<Texture>("../asset/texture/img.png");
		auto img1 = mgr.cache<Texture>("../asset/texture/second.png");
	}

	{
		auto bgm = mgr.cache<Sound>("../mwe/audio/bgm.ogg");
		auto sfx1 = mgr.cache<Sound>("../mwe/audio/sfx1.wav");
		auto sfx2 = mgr.cache<Sound>("../mwe/audio/sfx2.wav");

		auto img = mgr.cache<Texture>("../asset/texture/img.png");
		auto img1 = mgr.cache<Texture>("../asset/texture/second.png");
	}
}
