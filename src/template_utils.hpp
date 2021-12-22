#pragma once
#include <cstddef>

/**
 * \file template_utils.hpp
 * \brief Implements some magic template utilities
 */

template<std::size_t A, std::size_t B> struct add { static constexpr std::size_t value = A + B; };
template<std::size_t A, std::size_t B> struct mul { static constexpr std::size_t value = A * B; };

template<template<std::size_t, std::size_t> typename OP, std::size_t A, std::size_t ... R>
struct reduce { static constexpr std::size_t value = OP<A, reduce<OP, R...>::value>::value; };

template<template<std::size_t, std::size_t> typename OP, std::size_t N>
struct reduce<OP, N> { static constexpr std::size_t value = N; };

template<template<std::size_t, std::size_t> typename OP, std::size_t L, std::size_t N, std::size_t ... R>
struct reduce_n { static constexpr std::size_t value = L ? OP<N, reduce_n<OP, L - 1, R...>::value>::value : 1; };

template<template<std::size_t, std::size_t> typename OP, std::size_t L, std::size_t N>
struct reduce_n<OP, L, N> { static constexpr std::size_t value = L ? N : 1; };
