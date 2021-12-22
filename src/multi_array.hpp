#pragma once
#include <array>
#include <tuple>

#include "template_utils.hpp"

/**
 * \file multi_array.hpp
 * \brief Implements fancy multi-dimensional arrays
 */

/**
 * \typename multiarray_utils
 * \brief Contains static utilities for calculating multiarray indices using template magic
 * \tparam N The multiarray dimensions
 */
template<std::size_t ... N>
class multiarray_utils {
public:
	template<typename ... Args>
	constexpr static std::size_t index(std::size_t n, Args... args) {
		return n * reduce_n<mul, sizeof...(N) - sizeof...(Args) - 1, N...>::value +
			   multiarray_utils<N...>::index(args...);
	}

	template<typename ... Args>
	constexpr static std::size_t index() {
		return 0;
	}

	template<typename ... Args>
	constexpr static std::size_t circular_index(std::size_t n, Args... args) {
		return (n % std::get<sizeof...(N) - sizeof...(Args) - 1>(std::forward_as_tuple(N...))) *
			   reduce_n<mul, sizeof...(N) - sizeof...(Args) - 1, N...>::value +
			   multiarray_utils<N...>::index(args...);
	}

	template<typename ... Args>
	constexpr static std::size_t circular_index() {
		return 0;
	}
};

/**
 * \class multiarray
 * \brief Implements a multi-dimensional array, which can be indexed either using (x, y, ...) or linearly as [a]
 *
 * This is similar to e.g. how matrices in MATLAB work
 *
 * \tparam T The type of array elements
 * \tparam N The multiarray dimensions
 */
template<typename T, std::size_t ... N>
class multiarray : public std::array<T, reduce<add, N...>::value> {
public:
	template<typename ... Args>
	constexpr T& operator()(Args ... n) noexcept
	{
		return this->operator[](multiarray_utils<N...>::index(n...));
	}

	template<typename ... Args>
	constexpr const T& operator()(Args ... n) const noexcept
	{
		return this->operator[](multiarray_utils<N...>::index(n...));
	}
};

/**
 * \class circular_multiarray
 * \brief A variation of \a multiarray where the indices are circular (like circular buffers)
 *
 * \tparam T The type of array elements
 * \tparam N The array dimensions
 */
template<typename T, std::size_t ... N>
class circular_multiarray : public std::array<T, reduce<add, N...>::value> {
public:
	template<typename ... Args>
	constexpr T& operator()(Args ... n) noexcept
	{
		return this->operator[](multiarray_utils<N...>::circular_index(n...));
	}

	template<typename ... Args>
	constexpr const T& operator()(Args ... n) const noexcept
	{
		return this->operator[](multiarray_utils<N...>::circular_index(n...));
	}
};