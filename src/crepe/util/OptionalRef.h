#pragma once

namespace crepe {

/**
 * \brief Optional reference utility
 *
 * This class doesn't need to know the full definition of \c T to be used.
 *
 * \tparam T Value type
 */
template <typename T>
class OptionalRef {
public:
	//! Initialize empty (nonexistant) reference
	OptionalRef() = default;
	//! Initialize reference with value
	OptionalRef(T & ref);
	/**
	 * \brief Assign new reference
	 *
	 * \param ref Reference to assign
	 *
	 * \return Reference to this (required for operator)
	 */
	OptionalRef<T> & operator=(T & ref);
	/**
	 * \brief Check if this reference is not empty
	 *
	 * \returns `true` if reference is set, or `false` if it is not
	 */
	explicit operator bool() const noexcept;

	/**
	 * \brief Assign new reference
	 *
	 * \param ref Reference to assign
	 */
	void set(T &) noexcept;
	/**
	 * \brief Retrieve this reference
	 *
	 * \returns Internal reference if it is set
	 *
	 * \throws std::runtime_error if this function is called while the reference it not set
	 */
	T & get() const;
	/**
	 * \brief Make this reference empty
	 */
	void clear() noexcept;

	//! Copy constructor
	OptionalRef(const OptionalRef<T> &);
	//! Move constructor
	OptionalRef(OptionalRef<T> &&);
	//! Copy assignment
	OptionalRef<T> & operator=(const OptionalRef<T> &);
	//! Move assignment
	OptionalRef<T> & operator=(OptionalRef<T> &&);

private:
	/**
	 * \brief Reference to the value of type \c T
	 *
	 * \note This raw pointer is *not* managed, and only used as a reference!
	 */
	T * ref = nullptr;
};

} // namespace crepe

#include "OptionalRef.hpp"
