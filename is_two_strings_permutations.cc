/* Given two strings, determine if they are permutations of each other.
 * is_two_strings_permutations.cc
 *
 *  Created on: Jan 22, 2016
 *      Author: root
 */

#include <string>
#include "gtest/gtest.h"
#include <unordered_map>
#include <iostream>
using std::string;
using namespace std;

bool is_two_stirngs_permutations1(const char *str1, const char *str2)
{


	return true;
}

bool is_two_stirngs_permutations(const char *str1, const char *str2)
{
	string s1 = str1;
	string s2 = str2;

	std::cout << s1 << ", " << s2 << std::endl;

	if (s1.length() != s2.length())
		return false;

	std::unordered_map<char, int> strmap1;
	std::unordered_map<char, int> strmap2;
	for (int i = 0; i < s1.length(); ++i) {
			strmap1[s1[i]]++;
			strmap2[s2[i]]++;
	}

	for (auto &x: strmap1) {
		std::cout << x.first << ": " << x.second << std::endl;
	}

	if (strmap1.size() != strmap2.size())
		return false;

/*	for (auto &x: strmap1) {
		if (strmap1[x.first] != strmap2[x.first]) {
			return false;
		}
	}*/
//	std::unordered_map<char, int>::iterator it;
	for (auto it = strmap1.begin(); it != strmap1.end(); ++it) {
		if (it->second != strmap2[it->first])
			return false;
	}

	return true;
}

TEST(isUniqueChars, normal) {
	const char* str1 = "abcdac";
	const char* str2 = "cbacad";

	ASSERT_EQ(true, is_two_stirngs_permutations(str1, str2));
}

TEST(isUniqueChars, falsecase) {
	const char* str1 = "abcd";
	const char* str2 = "bacad";

	ASSERT_EQ(false, is_two_stirngs_permutations(str1, str2));
}

TEST(isUniqueChars, falsecase2) {
	const char* str1 = "adbce";
	const char* str2 = "bacad";

	ASSERT_EQ(false, is_two_stirngs_permutations(str1, str2));
}

