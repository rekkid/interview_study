/*
 * reverse_sentence.cc
 *
 * Given input -> "I have 36 books, 40 pens2."; output-> "I evah 36 skoob, 40 2snep."
 * (Suppose punctuation mark may only have period or comma)
 *
 *  Created on: Jan 27, 2016
 *      Author: root
 */

#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"
#include <string>
using namespace std;

void reverse_word(char *start, char *end) {
//	cout << idx_end << "\n";
	while (start < end) {
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
}

bool is_alphebit_or_number(char c) {
	return (c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z') ||
		   (c >= '0' && c <= '9');
}

bool is_punctuation_or_number(char c) {
	return c == ' ' ||
		   c == ',' ||
		   c == '.' ||
		   (c >= '0' && c <= '9');
}

void reverse_sentence(char *sentence) {
	int idx = 0;
	while (idx != strlen(sentence)) {
		while (is_punctuation_or_number(sentence[idx])) {
			idx++;
			continue;
		}
		int start = idx;
		while (is_alphebit_or_number(sentence[idx])) {
			idx++;
		}

		reverse_word(sentence + start, sentence + idx - 1);
	}
}

TEST(ReverseSentence, case1) {
	char str[100] = "I have 36 books, 40 pens2.";
//	char str[100] = "I have.";
	char word[] = "pens2";
	reverse_word(word, word + strlen(word) - 1);
	ASSERT_STREQ("2snep", word);

	reverse_sentence(str);

	ASSERT_STREQ("I evah 36 skoob, 40 2snep.", str);
}

TEST(ReverseSentence, case2) {
	char str[100] = "I.";
	reverse_sentence(str);
	ASSERT_STREQ("I.", str);
}

TEST(ReverseSentence, case3) {
	char str[100] = "4 a4.";
	reverse_sentence(str);
	ASSERT_STREQ("4 4a.", str);
}

TEST(ReverseSentence, case4) {
	char str[100] = " , . abcde  cad ";
	reverse_sentence(str);
	ASSERT_STREQ(" , . edcba  dac ", str);
}
