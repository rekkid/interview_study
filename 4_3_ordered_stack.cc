/*
 * 4_3_sort_stack.cc
 *
 * How to sort a stack in ascending order (i.e. pop in
 * ascending order) with another stack?
 *
 * 如何按照升序，使用另外一个栈来排序一个栈？例如，按照升序来pop
 *
 *  Created on: Feb 16, 2016
 *      Author: ZJ
 */

#include <stack>
#include "gtest/gtest.h"

using namespace std;

class OrderedStack {
public:
	void push(int value) {
		if (data.empty()) {
			data.push(value);
			return;
		}

		while (!data.empty() && data.top() < value) {
			back.push(data.top());
			data.pop();
		}
		data.push(value);
		while (!back.empty()) {
			data.push(back.top());
			back.pop();
		}
	}

	void pop() {
		data.pop();
	}

	int top() {
		int top = data.top();
		return top;
	}
private:
	stack<int> data;
	stack<int> back;
};

TEST(OrderedStack, case1) {
	OrderedStack s;

	s.push(1);
	s.push(5);
	s.push(2);
	s.push(7);

	ASSERT_EQ(1, s.top());
	s.pop();
	ASSERT_EQ(2, s.top());
	s.pop();
	ASSERT_EQ(5, s.top());
	s.pop();
	ASSERT_EQ(7, s.top());
}


