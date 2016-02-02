/*
 * replace_space_with_string.cc
 *
 * Replace space in the string with "%20". E.g. given "Big Mac".
 * Return "Big%20mac"
 *
 *  Created on: Jan 26, 2016
 *      Author: root
 */

#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"
#include <string>
using namespace std;

void replace_space_with_string(char *str) {
	char *replacing_str = "%20";
	int total_space = 0;
	int idx = 0;
	while (idx < (int)strlen(str)) {
		if (str[idx] != ' ') {
			idx++;
			continue;
		}
		while (str[idx] == ' ') {
			idx++;
			total_space++;
		}
	}
	cout << "total_space:" << total_space << "\n";

	int newstr_len = strlen(str) - total_space + total_space * strlen(replacing_str);
	int new_pos = newstr_len - 1;
	int old_pos = strlen(str) - 1;

	cout << "new_pos: " << new_pos << "\n";
	cout << "old_pos: " << old_pos << "\n";
	str[newstr_len + 1] = '\0';
	while (old_pos > 0) {
		if (str[old_pos] != ' ') {
			str[new_pos--] = str[old_pos--];
			continue;
		}
		while (str[old_pos] == ' ') {
			old_pos--;
			for (int i = strlen(replacing_str); i > 0; --i) {
				str[new_pos--] = replacing_str[i - 1];
			}
		}
	}
}

TEST(ReplaceSpaceWithString, case1) {
	char str[100] = "Big  mac";
	replace_space_with_string(str);

	ASSERT_STREQ("Big%20%20mac", str);
}

TEST(ReplaceSpaceWithString, case2) {
	char str[100] = "Big  mac   code  ";
	replace_space_with_string(str);

	ASSERT_STREQ("Big%20%20mac%20%20%20code%20%20", str);
}

TEST(ReplaceSpaceWithString, case3) {
	char str[100] = "  ";
	replace_space_with_string(str);

	ASSERT_STREQ("%20%20", str);
}

TEST(ReplaceSpaceWithString, case4) {
	char str[100] = "";
	replace_space_with_string(str);

	ASSERT_STREQ("", str);
}
