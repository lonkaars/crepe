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
private:
	/**
	 * \brief Prototype pattern clone function.
	 *
	 * \param src Source file of new resource (abstraction for file saved on
	 * disk)
	 *
	 * \returns New instance of concrete resource
	 */
	virtual std::unique_ptr<Resource> clone(const Asset & src) const = 0;
	/**
	 * The resource manager uses \c clone to create new instances of the concrete
	 * resource class. This may be used to inherit references to classes that
	 * would otherwise need to be implemented as singletons.
	 */
	friend class ResourceManager;
};

} // namespace crepe
