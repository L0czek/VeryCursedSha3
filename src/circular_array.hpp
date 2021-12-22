#pragma once
#include <array>

/**
 * \file circular_array.hpp
 * \brief Implements an array with modulo indices (like a circular buffer)
 */

template<typename T, std::size_t N>
class circulararray :public std::array<T, N> {
public:
	T& operator[](int n) {
		return std::array<T, N>::operator[](n % 5);
	}
	const T& operator[](int n) const {
		return std::array<T, N>::operator[](n % 5);
	}
};