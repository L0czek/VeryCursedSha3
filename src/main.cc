#include <iostream>
#include <algorithm>
#include <bitset>
#include <array>
#include <type_traits>
#include <numeric>
#include <bit>
#include <tuple>

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

template<std::size_t A, std::size_t B> struct add { static constexpr std::size_t value = A + B; };
template<std::size_t A, std::size_t B> struct mul { static constexpr std::size_t value = A * B; };

template<template<std::size_t, std::size_t> typename OP, std::size_t A, std::size_t ... R>
struct reduce { static constexpr std::size_t value = OP<A, reduce<OP, R...>::value>::value; };

template<template<std::size_t, std::size_t> typename OP, std::size_t N> struct reduce<OP, N> { static constexpr std::size_t value = N; };

template<template<std::size_t, std::size_t> typename OP, std::size_t L, std::size_t N, std::size_t ... R>
struct reduce_n { static constexpr std::size_t value = L ? OP<N, reduce_n<OP, L - 1, R...>::value>::value : 1; };

template<template<std::size_t, std::size_t> typename OP, std::size_t L, std::size_t N>
struct reduce_n<OP, L, N> { static constexpr std::size_t value = L ? N : 1; };

template<typename F, typename ... T>
struct append_back {
    using type = std::tuple<T..., F>;
};

template<typename F, typename ... T>
struct revert {
    using type = typename append_back<F, typename revert<T...>::type>::type;
};

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

template<std::size_t R, std::size_t L, std::size_t C>
constexpr std::size_t row_size() {
    static_assert(25 * (1 << L) == R + C);
    return 1 << L;
}

namespace std {

template<std::size_t N>
constexpr std::bitset<N> rotl(const std::bitset<N>& x, int s) noexcept {
    return (x << s) | ((x >> (N - s)) & (std::bitset<N>().set() << s));
}

}

template<std::size_t L, std::size_t R, std::size_t C>
class Keccak {
public:

    void absorb(const std::bitset<R>& in) {

    }

private:
    using RowType = std::bitset<row_size<R, L, C>()>;
    using StateType = multiarray<circulararray, RowType, 5, 5>;

    StateType state;

    void f(std::size_t nr) {
        theta();
        const auto b = rho_pi();
        chi(b);
        iota(nr);
    }

    void theta() noexcept {
        circulararray<RowType, 5> c;
        circulararray<RowType, 5> d;

        for (std::size_t i=0; i < c.size(); ++i) {
            c[i] = std::reduce(state[i].begin(), state[i].end(), RowType(), [] (auto x, auto y) { return x ^ y; });
            d[i] = c[i - 1] ^ std::rotl(c[i + 1], 1);

            for (std::size_t j=0; j < state[i].size(); ++j) {
                state[i][j] ^= d[i];
            }
        }
    }

    StateType rho_pi() const noexcept {
        StateType b;

        for (std::size_t i=0; i < state.size(); ++i) {
            for (std::size_t j=0; j < state[i].size(); ++j) {
                b[j][2 * i + 3 * j] = std::rotl(state[i][j], r[i][j]);
            }
        }

        return b;
    }

    void chi(const StateType& b) noexcept {
        for (std::size_t i=0; i < state.size(); ++i) {
            for (std::size_t j=0; j < state[i].size(); ++j) {
                state[i][j] = b[i][j] ^ ((~b[i + 1][j]) & b[i + 2][j]);
            }
        }
    }

    void iota(std::size_t nr) noexcept {
        state[0][0] ^= rc[nr];
    }

    inline static const multiarray<std::array, std::size_t, 5, 5> r = { {
        {  0,  1, 62, 28, 27 },
        { 36, 44, 6 , 55, 20 },
        {  3, 10, 43, 25, 39 },
        { 41, 45, 15, 21,  8 },
        { 18,  2, 61, 56, 14 },
    } };

    inline static const std::array<RowType, 24> rc = { {
        { 0x0000000000000001 },
        { 0x0000000000008082 },
        { 0x800000000000808A },
        { 0x8000000080008000 },
        { 0x000000000000808B },
        { 0x0000000080000001 },
        { 0x8000000080008081 },
        { 0x8000000000008009 },
        { 0x000000000000008A },
        { 0x0000000000000088 },
        { 0x0000000080008009 },
        { 0x000000008000000A },
        { 0x000000008000808B },
        { 0x800000000000008B },
        { 0x8000000000008089 },
        { 0x8000000000008003 },
        { 0x8000000000008002 },
        { 0x8000000000000080 },
        { 0x000000000000800A },
        { 0x800000008000000A },
        { 0x8000000080008081 },
        { 0x8000000000008080 },
        { 0x0000000080000001 },
        { 0x8000000080008008 },
    } };

};


int main() {
    std::cout << utils<5, 10>::index(4, 5) << "\n";
}
