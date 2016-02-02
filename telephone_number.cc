/*
 * telephone_number.cc
 *
 *  Created on: Jan 16, 2016
 *      Author: root
 */

/*-------------------------------------
 *   日期：2015-03-30
 *   作者：SJF0115
 *   题目: 电话号码对应英语单词
 *   来源：百度
 *   博客：
 ------------------------------------*/
#include <iostream>
#include <vector>
using namespace std;

//每个数字键对应的字母个数
vector<int> count = { 0, 0, 3, 3, 3, 3, 3, 4, 3, 4 };
vector<string> letter = { "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS",
		"TUV", "WXYZ" };

// phone 电话号码 n 电话号码位数 index
void RecursiveSearch(vector<int> phone, vector<char> &path, int index, int n,
		vector<vector<char> > &result) {
	if (index == n) {
		result.push_back(path);
		return;
	} //if
	int num = phone[index];
	for (int i = 0; i < count[num]; ++i) {
		path.push_back(letter[num][i]);
		RecursiveSearch(phone, path, index + 1, n, result);
		path.pop_back();
	} //for
	if (count[num] == 0) {
		RecursiveSearch(phone, path, index + 1, n, result);
	} //if
}
// 非递归
vector<vector<char> > NoRecursiveSearch(vector<int> phone) {
	vector<vector<char> > result;
	vector<char> path;
	int size = phone.size();
	if (size <= 0) {
		return result;
	} //if
	  // 数字键目前所代表的字符在所能代表的字符集中的位置
	vector<int> answer(size, 0);
	while (true) {
		for (int i = 0; i < size; ++i) {
			path.push_back(letter[phone[i]][answer[i]]);
		}        //for
		result.push_back(path);
		path.clear();

		int k = size - 1;
		// 每一个数字对应的字母位置
		while (k >= 0) {
			if (answer[k] < count[phone[k]] - 1) {
				answer[k]++;
				break;
			}        //if
			else {
				answer[k] = 0;
				k--;
			}        //else
		}        //while
		if (k < 0) {
			break;
		}        //if
	}        //while
}

// 打印
void Print(vector<vector<char> > result) {
	for (int i = 0; i < result.size(); ++i) {
		for (int j = 0; j < result[i].size(); ++j) {
			cout << result[i][j];
		}        //for
		cout << endl;
	}        //for
}

int main() {
	vector<vector<char> > result;
	vector<char> path;
	vector<int> phone = { 3, 2, 4 };

	RecursiveSearch(phone, path, 0, phone.size(), result);
	Print(result);
	cout << endl;

	result = NoRecursiveSearch(phone);
	Print(result);
}

