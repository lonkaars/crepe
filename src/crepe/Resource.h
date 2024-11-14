#pragma once

#include <memory>

namespace crepe {

class ResourceManager;
class Asset;

/**
 * Resource is an interface class used to represent a (deserialized) game
 * resource (e.g. textures, sounds).
 */
class Resource {
public:
	Resource(const Asset & src);

private:
	/**
	 * The resource manager uses \c clone to create new instances of the concrete
	 * resource class. This may be used to inherit references to classes that
	 * would otherwise need to be implemented as singletons.
	 */
	friend class ResourceManager;
};

} // namespace crepe
