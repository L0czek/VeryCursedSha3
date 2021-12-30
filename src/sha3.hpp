#pragma once
#include <iostream>
#include <bitset>
#include <iterator>
#include <type_traits>
#include <numeric>
#include <bit>
#include <vector>

#include "multi_array.hpp"
#include "bitset_rot.hpp"

template<std::size_t L, std::size_t R, std::size_t C, typename RowT = std::bitset<1 << L>>
class KeccakF_ {
public:
    static_assert(25 * (1 << L) == R + C);
    constexpr static const std::size_t ROUNDS = 24;
    constexpr static const std::size_t row_size = 1 << L;

    using RowType = RowT;
    using StateType = circular_multiarray<RowType, 5, 5>;

    StateType state;

    KeccakF_()
    {
        reset();
    }

    void reset() {
        for(int i = 0; i < 25; ++i)
            state[i] = 0;
    }

    void f() {
        for(std::size_t roundNr = 0; roundNr < ROUNDS; ++roundNr) {
            theta();
            const auto b = rho_pi();
            chi(b);
            iota(roundNr);
        }
    }

    void theta() noexcept {
        circular_multiarray<RowType, 5> c;
        circular_multiarray<RowType, 5> d;

        for (std::size_t i=0; i < 5; ++i) {
            c(i) = RowType();
            for(std::size_t j = 0; j < 5; ++j)
                c(i) ^= state(i, j);
        }
        for (std::size_t i=0; i < 5; ++i) {
            d(i) = c(i - 1) ^ std::rotl(c(i + 1), 1);
        }
        for (std::size_t i=0; i < 5; ++i) {
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

    inline static const multiarray<RowType, ROUNDS> rc = { {
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
    } };

};

template<std::size_t L, std::size_t R, std::size_t C>
class KeccakF : public KeccakF_<L, R, C>
{
};

// When dealing with a standard value of l, we can just use "uint64_t" instead of std::bitset to speed up
// computations
template<std::size_t R, std::size_t C>
class KeccakF<6, R, C> : public KeccakF_<6, R, C, uint64_t>
{
    static_assert(sizeof(unsigned long)*8 == 1<<6);
};

// Now that we have KeccakF, define Keccak algorithm itself
template<std::size_t L, std::size_t R, std::size_t C, std::size_t D>
class Keccak : public KeccakF<L, R, C>
{
    static_assert(D % 8 == 0);
    // TODO: implement absorb/squeeze for arbitrary L
    
};

template<std::size_t R, std::size_t C, std::size_t D>
class Keccak<6, R, C, D> : public KeccakF<6, R, C>
{
public:
    static constexpr unsigned char PaddingLastByte = static_cast<unsigned char>(0x80);
    static constexpr unsigned char PaddingFirstByte = static_cast<unsigned char>(0x06);
    static_assert(D % 8 == 0);
    static_assert(R % 64 == 0);

    using Block = std::array<uint8_t, R/8>;
    using Digest = std::array<uint8_t, D/8>;
    
    template<std::random_access_iterator Iterator>
    Keccak& hash(Iterator begin, Iterator end) {
        Block block;
        block.fill(0);

        auto it = begin;
        while (static_cast<std::size_t>(std::distance(it, end)) > block.size()) {
            it = std::next(it, block.size());
            std::copy(begin, it, block.begin());
            absorb(block);
            KeccakF<6, R, C>::f();
            begin = std::next(begin, block.size());
        }

        block.fill(0);
        std::copy(it, end, block.begin());
        const auto index = std::distance(it, end);
        block[index] = 0x06;
        block.back() ^= 0x80;
        absorb(block);
        KeccakF<6, R, C>::f();
        return *this;
    }

    Digest digest() {
        // Squeeze the hash and return the digest (the first D bits of the squeezed output)
        // TODO: assumes that one squeezed block is enough because that is the case for SHA3 and I'm lazy
        static_assert(D < R);
        Block squeezed = this->squeeze();
        Digest digest;
        std::copy(squeezed.begin(), squeezed.begin() + digest.size(), digest.begin());
        return digest;
    }

    std::string hexdigest() {
        const auto hex = "01234567890abcdef";
        std::string ret;
        for (const auto & i : digest()) {
            ret += hex[i >> 4];
            ret += hex[i & 0xf];
        }
        
        return ret;
    }

    void absorb(const Block& block) {
        unsigned char* state_data = reinterpret_cast<unsigned char*>(this->state.data());
        for(std::size_t i = 0; i < block.size(); ++i) {
            state_data[i] ^= block[i];
        }
    }

    Block squeeze() {
        unsigned char* state_data = reinterpret_cast<unsigned char*>(this->state.data());
        Block out;
        for(std::size_t i = 0; i < out.size(); ++i) {
            out[i] = state_data[i];
        }
        return out;
    }
};

using SHA3_224 = Keccak<6, 1152, 448, 224>;
using SHA3_256 = Keccak<6, 1088, 512, 256>;
using SHA3_384 = Keccak<6, 832, 768, 384>;
using SHA3_512 = Keccak<6, 576, 1024, 512>;
