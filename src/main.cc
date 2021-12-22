#include <iostream>
#include <bitset>
#include <array>
#include <type_traits>
#include <numeric>
#include <bit>

#include "multi_array.hpp"
#include "circular_array.hpp"

/*template<std::size_t R, std::size_t L, std::size_t C>
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

};*/


int main() {
    std::cout << multiarray_utils<5, 10>::index(4, 5) << "\n";

    multiarray<int, 5, 5> arr;
    arr(1, 1) = 17;
    std::cout << arr(1, 1) << std::endl;
}
