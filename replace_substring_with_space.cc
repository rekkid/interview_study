/*
 * replace_string_with_space.cc
 *
 * Replace "%20" substring with space. E.g. given
 * "Big%20mac", return "Big mac"
 *
 *  Created on: Jan 27, 2016
 *      Author: root
 */

#include <vector>
#include <unordered_map>
#include <string>
#include "gtest/gtest.h"

using namespace std;

void replace_substring_with_space(char *str) {
	int len = (int)strlen(str);
	char substring[] = "%20";

	if (len < (int)strlen(substring)) {
		return;
	}
	int new_pos = 0;
	for (int old_pos = 0; old_pos < len;) {
		if (str[old_pos] == '%' && str[old_pos + 1] == '2' && str[old_pos + 2] == '0') {
			old_pos += strlen(substring);
			str[new_pos++] = ' ';
		} else{
			str[new_pos++] = str[old_pos++];
		}
	}
	str[new_pos] = '\0';
}

TEST(ReplaceSpaceWithString, case1) {
	char str[100] = "Big%20mac";
	replace_substring_with_space(str);

	ASSERT_STREQ("Big mac", str);
}

TEST(ReplaceSpaceWithString, case2) {
	char str[100] = "Big%20%20mac";
	replace_substring_with_space(str);

	ASSERT_STREQ("Big  mac", str);
}

TEST(ReplaceSpaceWithString, case3) {
	char str[100] = "Bi";
	replace_substring_with_space(str);

	ASSERT_STREQ("Bi", str);

	strcpy(str, "Big%%20 ");
	replace_substring_with_space(str);
	ASSERT_STREQ("Big%  ", str);
}
