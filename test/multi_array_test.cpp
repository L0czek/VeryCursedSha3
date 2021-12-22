#include <gtest/gtest.h>

#include "../src/multi_array.hpp"

static_assert(std::is_base_of<std::array<int, 25>, multiarray<int, 5, 5>>::value);
TEST(MultiArrayTest, NormalMultiArrayIndexTest) {
	for(int y = 0; y < 5; ++y) {
		for(int x = 0; x < 5; ++x) {
			int i = multiarray_utils<5, 5>::index(x, y);
			EXPECT_EQ(i, y*5 + x) << "at index (" << x << ", " << y << ")";
		}
	}
}
TEST(MultiArrayTest, NormalMultiArrayReadTest) {
	multiarray<int, 5, 5> arr;
	for(int i = 0; i < 25; ++i)
		arr[i] = i;
	for(int y = 0; y < 5; ++y) {
		for(int x = 0; x < 5; ++x) {
			EXPECT_EQ(arr(x, y), y*5 + x) << "at index (" << x << ", " << y << ")";
		}
	}
}
TEST(MultiArrayTest, NormalMultiArrayWriteTest) {
	multiarray<int, 5, 5> arr;
	for(int y = 0; y < 5; ++y) {
		for(int x = 0; x < 5; ++x) {
			arr(x, y) = y*5 + x;
		}
	}
	for(int i = 0; i < 25; ++i)
		EXPECT_EQ(arr[i], i) << "at index " << i;
}

static_assert(std::is_base_of<std::array<int, 25>, circular_multiarray<int, 5, 5>>::value);
TEST(MultiArrayTest, CircularMultiArrayIndexTest) {
	for(int y = 0; y < 5; ++y) {
		for(int x = 0; x < 5; ++x) {
			int i = multiarray_utils<5, 5>::circular_index(x, y);
			EXPECT_EQ(i, (y%5)*5 + (x%5)) << "at index (" << x << ", " << y << ")";
		}
	}
}
TEST(MultiArrayTest, CircularMultiArrayReadTest) {
	circular_multiarray<int, 5, 5> arr;
	for(int i = 0; i < 25; ++i)
		arr[i] = i;
	for(int y = 0; y < 10; ++y) {
		for(int x = 0; x < 10; ++x) {
			EXPECT_EQ(arr(x, y), (y%5)*5 + (x%5)) << "at index (" << x << ", " << y << ")";
		}
	}
}
TEST(MultiArrayTest, CircularMultiArrayWriteTest) {
	circular_multiarray<int, 5, 5> arr;
	for(int y = 5; y < 10; ++y) {
		for(int x = 5; x < 10; ++x) {
			arr(x, y) = (y%5)*5 + (x%5);
		}
	}
	for(int i = 0; i < 25; ++i)
		EXPECT_EQ(arr[i], i) << "at index " << i;
}