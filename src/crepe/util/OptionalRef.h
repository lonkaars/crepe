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
	OptionalRef() = default;
	OptionalRef(T &);
  OptionalRef<T> & operator=(T &);
	explicit operator bool() const noexcept;

	void set(T &) noexcept;
	T & get() const;
	void clear() noexcept;

  OptionalRef(const OptionalRef<T> &);
  OptionalRef(OptionalRef<T> &&);
  OptionalRef<T> & operator=(const OptionalRef<T> &);
  OptionalRef<T> & operator=(OptionalRef<T> &&);

private:
	/**
	 * \brief Reference to the value of type \c T
	 *
	 * \note This raw pointer is *not* managed, and only used as a reference!
	 */
	T * ref = nullptr;
};

}

#include "OptionalRef.hpp"

