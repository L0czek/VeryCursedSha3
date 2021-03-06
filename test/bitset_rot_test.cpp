#include <gtest/gtest.h>

#include "../src/bitset_rot.hpp"

TEST(BitsetRotTest, BitsetRotTest) {
    EXPECT_EQ(rotl(std::bitset<64>(0x0123456789ABCDEF), 8), std::bitset<64>(0x23456789ABCDEF01));
    EXPECT_EQ(rotl(std::bitset<64>(0x8000000000000000), 8), std::bitset<64>(0x0000000000000080));
    EXPECT_EQ(rotl(std::bitset<64>(0x8000000000000001), 1), std::bitset<64>(0x0000000000000003));
}
TEST(BitsetRotTest, NormalRotTest) {
    EXPECT_EQ(rotl(0x0123456789ABCDEFULL, 8), 0x23456789ABCDEF01ULL);
    EXPECT_EQ(rotl(0x8000000000000000ULL, 8), 0x0000000000000080ULL);
    EXPECT_EQ(rotl(0x8000000000000001ULL, 1), 0x0000000000000003ULL);
}
