#pragma once
#include <iostream>
#include <bitset>
#include <type_traits>
#include <numeric>
#include <bit>

#include "multi_array.hpp"
#include "bitset_rot.hpp"

template<std::size_t L, std::size_t R, std::size_t C>
class Keccak {
public:
	static_assert(25 * (1 << L) == R + C);
	constexpr static const std::size_t row_size = 1 << L;

    using RowType = std::bitset<row_size>;
    using StateType = circular_multiarray<RowType, 5, 5>;

    StateType state;

	void load_state(std::array<unsigned long, 25> input_state) {
		static_assert(sizeof(unsigned long) == 8);
		for(int i = 0; i < 25; ++i)
			state[i] = input_state[i];
	}

    std::array<unsigned long, 25> dump_state() {
    	static_assert(sizeof(unsigned long) == 8);
		std::array<unsigned long, 25> out;
		for(int i = 0; i < 25; ++i)
			out[i] = state[i].to_ulong();
		return out;
    }

    void f(std::size_t nr) {
        theta();
        const auto b = rho_pi();
        chi(b);
        iota(nr);
    }

    void theta() noexcept {
		circular_multiarray<RowType, 5> c;
		circular_multiarray<RowType, 5> d;

        for (std::size_t i=0; i < 5; ++i) {
            c(i) = RowType();
            for(std::size_t j = 0; j < 5; ++j)
            	c(i) ^= state(i, j);
            d(i) = c(i - 1) ^ std::rotl(c(i + 1), 1);

            for (std::size_t j=0; j < 5; ++j) {
                state(i, j) ^= d(i);
            }
        }
    }

    StateType rho_pi() const noexcept {
        StateType b;

        for (std::size_t i=0; i < 5; ++i) {
            for (std::size_t j=0; j < 5; ++j) {
                b(j, 2 * i + 3 * j) = std::rotl(state(i, j), r(i, j));
            }
        }

        return b;
    }

    void chi(const StateType& b) noexcept {
        for (std::size_t i=0; i < 5; ++i) {
            for (std::size_t j=0; j < 5; ++j) {
                state(i, j) = b(i, j) ^ ((~b(i + 1, j)) & b(i + 2, j));
            }
        }
    }

    void iota(std::size_t nr) noexcept {
        state(0, 0) ^= rc(nr);
    }

    inline static const multiarray<std::size_t, 5, 5> r = { {
          0,  1, 62, 28, 27,
         36, 44, 6 , 55, 20,
          3, 10, 43, 25, 39,
         41, 45, 15, 21,  8,
         18,  2, 61, 56, 14,
    } };

    inline static const multiarray<RowType, 24> rc = {
        0x0000000000000001,
        0x0000000000008082,
        0x800000000000808A,
        0x8000000080008000,
        0x000000000000808B,
        0x0000000080000001,
        0x8000000080008081,
        0x8000000000008009,
        0x000000000000008A,
        0x0000000000000088,
        0x0000000080008009,
        0x000000008000000A,
        0x000000008000808B,
        0x800000000000008B,
        0x8000000000008089,
        0x8000000000008003,
        0x8000000000008002,
        0x8000000000000080,
        0x000000000000800A,
        0x800000008000000A,
        0x8000000080008081,
        0x8000000000008080,
        0x0000000080000001,
        0x8000000080008008,
    };

};

using SHA3_224 = Keccak<6, 1152, 448>;
using SHA3_256 = Keccak<6, 1088, 512>;
using SHA3_384 = Keccak<6, 832, 768>;
using SHA3_512 = Keccak<6, 576, 1024>;
