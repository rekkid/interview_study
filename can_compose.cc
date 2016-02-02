/*
 * can_compose.cc
 *
 * Given a newspaper and message as two strings, check if the message
 * can be composed using letters in the newspaper.
 *
 *  Created on: Jan 23, 2016
 *      Author: root
 */

#include <string>
#include <unordered_map>
#include <gtest/gtest.h>
using namespace std;

bool can_compose(string newspaper, string message) {
	unordered_map<char, int> newspaper_map;
	for (auto c : newspaper) {
		newspaper_map[c]++;
	}

	unordered_map<char, int> message_map;
	for (auto c : message) {
		message_map[c]++;
	}

	for (auto &item : message_map) {
		if (item.second > newspaper_map[item.first]) {
			return false;
		}
	}

	return true;
}

TEST(canCompose, normal) {
	string newspaper = "abcdefghijkl";
	string message = "hka";

	ASSERT_EQ(true, can_compose(newspaper, message));
}

TEST(canCompose, falsecase) {
	string newspaper = "abcdefghijkl";
	string message = "hkaa";

	ASSERT_EQ(false, can_compose(newspaper, message));
}

TEST(canCompose, falsecase2) {
	string newspaper = "abcdefghijkl";
	string message = "hkaam";

	ASSERT_EQ(false, can_compose(newspaper, message));
}
