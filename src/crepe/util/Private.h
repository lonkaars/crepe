#pragma once

#include <functional>
#include <typeindex>

namespace crepe {

/**
 * \brief Utility for storing type hidden from user
 *
 * This class can be used to store types which cannot be used in the API directly due to header
 * distribution limitations. This class is similar to `std::any`, but provides a method for
 * retrieving a mutable reference to the stored object.
 */
class Private {
public:
	Private() = default;
	~Private();
	/**
	 * \name Copy
	 *
	 * \note These functions do not do anything, resulting in `*this` being an empty (default)
	 * instance.
	 *
	 * \{
	 */
	Private(const Private &);
	Private & operator=(const Private &);
	//! \}
	/**
	 * \name Move
	 *
	 * These functions actually move the stored type if present.
	 *
	 * \{
	 */
	Private(Private &&);
	Private & operator=(Private &&);
	//! \}

	/**
	 * \brief Get the stored object
	 *
	 * \tparam T Type of stored object
	 *
	 * \returns Mutable reference to stored object
	 *
	 * \throws std::out_of_range if this instance does not contain any object
	 * \throws std::logic_error if the stored type and requested type differ
	 */
	template <typename T>
	T & get() const;

	/**
	 * \brief Create and store an arbitrary object
	 *
	 * \tparam T Type of object
	 * \tparam Args Perfect forwarding arguments
	 * \param args Perfect forwarding arguments
	 *
	 * All arguments to this function are forwarded using `std::forward` to the constructor of T.
	 *
	 * \returns Mutable reference to stored object
	 *
	 * \note If this instance already contained an object, this function implicitly destroys the
	 * previous object.
	 */
	template <typename T, typename... Args>
	T & set(Args &&... args);

	/**
	 * \brief Check if this instance contains an object
	 *
	 * \returns `true` if this instance is empty, `false` if it contains an object
	 */
	bool empty() const noexcept;

private:
	//! Wrapper for destructor call of stored object type
	std::function<void(void *)> destructor;
	//! Stored object's type
	std::type_index type = typeid(void);
	//! Stored object
	void * instance = nullptr;
};

} // namespace crepe

#include "Private.hpp"
