#pragma once
#include <array>

#include "template_utils.hpp"

/**
 * \file multi_array.hpp
 * \brief Implements a multi-dimensional array, which can be indexed either using (x, y, ...) or linearly as [a]
 *
 * This is similar to e.g. how matrices in MATLAB work
 */

template<std::size_t ... N>
class multiarray_utils {
public:
	template<typename ... Args>
	static std::size_t index(std::size_t n, Args... args) {
		return n * reduce_n<mul, sizeof...(N) - sizeof...(Args) - 1, N...>::value +
			   multiarray_utils<N...>::index(args...);
	}

	template<typename ... Args>
	static std::size_t index() {
		return 0;
	}
};

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