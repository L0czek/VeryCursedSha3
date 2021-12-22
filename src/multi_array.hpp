#pragma once
#include <array>

#include "template_utils.hpp"

/**
 * \file multi_array.hpp
 * \brief Implements a multi-dimensional array, which can be indexed either using (x, y, ...) or linearly as (a)
 *
 * This is similar to e.g. how matrices in MATLAB work
 */

template<std::size_t ... N>
class utils {
public:
	template<typename ... Args>
	static std::size_t index(std::size_t n, Args... args) {
		return n * reduce_n<mul, sizeof...(N) - sizeof...(Args) - 1, N...>::value +
			   utils<N...>::index(args...);
	}

	template<typename ... Args>
	static std::size_t index() {
		return 0;
	}
};

template<typename T, std::size_t ... N>
class array :public std::array<T, reduce<add, N...>::value> {

public:
	template<typename ... Args>
	T& operator()(Args ... n) noexcept {
	}
};

template<template<typename, std::size_t> typename base, typename T, std::size_t N1, std::size_t ... R>
struct InduceMultiArray{
	using type = base<typename InduceMultiArray<base, T, R...>::type, N1>;
};

template<template<typename, std::size_t> typename base, typename T, std::size_t N>
struct InduceMultiArray<base, T, N> {
	using type = base<T, N>;
};

template<template<typename, std::size_t> typename base, typename T, std::size_t N1, std::size_t ... R>
using multiarray = typename InduceMultiArray<base, T, N1, R...>::type;