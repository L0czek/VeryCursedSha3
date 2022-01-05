#pragma once
#include <bitset>

/**
 * \file bitset_rot.hpp
 * \brief A modified version of std::rotl with support for std::bitset and no support for negative arguments (for performance)
 */

template<typename T>
constexpr T rotl(const T x, int s) noexcept {
    constexpr auto N = std::numeric_limits<T>::digits;
    return (x << s) | (x >> (N - s));
}

template<std::size_t N>
constexpr std::bitset<N> rotl(const std::bitset<N>& x, int s) noexcept {
    return (x << s) | (x >> (N - s));
}
