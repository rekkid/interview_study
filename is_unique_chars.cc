/*
 * is_unique_chars.cc
 *
 *  Created on: Jan 21, 2016
 *      Author: root
 */


#include "gtest/gtest.h"

bool is_unique_chars(const char *array)
{
	bool map[256] = {};

	for (int i = 0; i < strlen(array); ++i) {
		if (!map[array[i]]) {
			map[array[i]] = true;
		} else {
			return false;
		}
	}
	return true;
}

TEST(isUniqueChars, normal) {
	char *array = "abcdefg";

	ASSERT_EQ(true, is_unique_chars(array));
}


TEST(isUniqueChars, falsetest) {
	char *array = "abcdefa";

	ASSERT_EQ(false, is_unique_chars(array));
}

TEST(isUniqueChars, nullchar) {
	char *array = "";

	ASSERT_EQ(true, is_unique_chars(array));
}

TEST(isUniqueChars, onchar) {
	char *array = "a";

	ASSERT_EQ(true, is_unique_chars(array));
}
