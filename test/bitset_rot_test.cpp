#include <gtest/gtest.h>

#include "../src/bitset_rot.hpp"

TEST(BitsetRotTest, BitsetRotTest) {
	EXPECT_EQ(std::rotl(std::bitset<64>(0x0123456789ABCDEF), 8), std::bitset<64>(0x23456789ABCDEF01));
	EXPECT_EQ(std::rotl(std::bitset<64>(0x8000000000000000), 8), std::bitset<64>(0x0000000000000080));
	EXPECT_EQ(std::rotl(std::bitset<64>(0x8000000000000001), 1), std::bitset<64>(0x0000000000000003));
}