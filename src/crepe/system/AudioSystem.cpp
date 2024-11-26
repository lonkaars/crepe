#include "AudioSystem.h"
#include "ComponentManager.h"

#include "../api/AudioSource.h"

using namespace crepe;
using namespace std;

void AudioSystem::update() {
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<AudioSource>> components = mgr.get_components_by_type<AudioSource>();

	for (auto component_ref : components) {
		AudioSource & component = component_ref.get();
		if (!component.active) continue;

		/**
		 * How this is supposed to work:
		 * - Get an instance of Sound for this resource/component combo (Sound
		 *   instance is supposed to be unique per component, even if they use the
		 *   same underlying asset).
		 * OR
		 * - Use the same instance of Sound if this is what the cache returns
		 *   (= what the game programmer's wishes to do).
		 *
		 * NOT supposed to happen but still the case:
		 * - Below function call causes assets to be cached unintentionally
		 * - Cached assets are deleted at the end of a scene (i think?)
		 * - I'm not sure if the ResourceManager is even supposed to have a public
		 *   `.clear()` method since the control over resource lifetime is
		 *   explicitly handed over to the game programmer by using ResourceManager
		 *   to cache/uncache. I believe the proper methods are supposed to be:
		 *
		 *   - get()       get a reference to resource (used here)
		 *   - clear()     clears NON-cached assets
		 *   - cache()     marks asset as "do not delete at end of scene"
		 *   - uncache()   undoes the above
		 *
		 *   I think somewhere in the above function calls a unique identifier for
		 *   the Asset/GameObject should be given to make sure the unique instance
		 *   shit works as intended. The resource manager is also used for things
		 *   other than sounds.
		 *
		 * Also need to check:
		 * - Is it an issue if there are multiple AudioSource components playing
		 *   the same sample (= identical Asset), while they are all triggered
		 *   using the same underlying instance of Sound (esp. w/
		 *   play/pause/retrigger behavior).
		 */
		// Sound & sound = this->resource_manager.get<Sound>(component);

		// TODO: lots of state diffing
	}
}

