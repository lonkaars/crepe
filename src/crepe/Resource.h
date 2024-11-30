#pragma once

namespace crepe {

class ResourceManager;
class Asset;

/**
 * \brief Resource interface
 *
 * Resource is an interface class used to represent a (deserialized) game resource (e.g.
 * textures, sounds). Resources are always created from \ref Asset "assets" by ResourceManager.
 *
 * The game programmer has the ability to use the ResourceManager to keep instances of concrete
 * resources between scenes, preventing them from being reinstantiated during a scene
 * transition.
 */
class Resource {
public:
	Resource(const Asset & src);
	virtual ~Resource() = default;
};

} // namespace crepe
