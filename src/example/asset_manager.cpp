#include <crepe/api/AssetManager.h>
#include <crepe/api/Texture.h>
#include <crepe/facade/Sound.h>

using namespace crepe;

int main() {

	// this needs to be called before the asset manager otherwise the destructor
	// of sdl is not in the right order
	{ Texture test("asset/texture/img.png"); }
	// FIXME: make it so the issue described by the above comment is not possible
	// (i.e. the order in which internal classes are instantiated should not
	// impact the way the engine works).

	auto & mgr = AssetManager::get_instance();

	{
		// TODO: [design] the Sound class can't be directly included by the user as
		// it includes SoLoud headers.
		auto bgm = mgr.cache<Sound>("mwe/audio/bgm.ogg");
		auto sfx1 = mgr.cache<Sound>("mwe/audio/sfx1.wav");
		auto sfx2 = mgr.cache<Sound>("mwe/audio/sfx2.wav");

		auto img = mgr.cache<Texture>("asset/texture/img.png");
		auto img1 = mgr.cache<Texture>("asset/texture/second.png");
	}

	{
		auto bgm = mgr.cache<Sound>("mwe/audio/bgm.ogg");
		auto sfx1 = mgr.cache<Sound>("mwe/audio/sfx1.wav");
		auto sfx2 = mgr.cache<Sound>("mwe/audio/sfx2.wav");

		auto img = mgr.cache<Texture>("asset/texture/img.png");
		auto img1 = mgr.cache<Texture>("asset/texture/second.png");
	}
}
