#pragma once
#include <bitset>

/**
 * \file bitset_rot.hpp
 * \brief Extends std::rotl to support std::bitset
 */

namespace std {
	template<std::size_t N>
	constexpr std::bitset<N> rotl(const std::bitset<N>& x, int s) noexcept {
		return (x << s) | ((x >> (N - s)) & ~(std::bitset<N>().set() << s));
	}
}