/*
 * 3_2_midpoint.cc
 *
 * Given a linked list, write a function to return the middle point of that list.
 *
 *  Created on: Jan 30, 2016
 *      Author: root
 */

#include <vector>
#include <unordered_map>
#include <string>
#include "gtest/gtest.h"

using namespace std;

class ListNode {
public:
	int value_;
	ListNode *next_;
public:
	ListNode(int value) : value_(value), next_(NULL) {}
};

class List {
public:
	ListNode *head_;
public:
	List() : head_(NULL) {}
	void AddFromHead(ListNode* node) {
		if (!node)
			return;

		if (head_ == NULL) {
			head_ = node;
		} else {
			node->next_ = head_;
			head_ = node;
		}
	}

	void Construct(const vector<int>& nodes_value) {
		vector<int>::const_reverse_iterator it;
		for (it = nodes_value.rbegin(); it != nodes_value.rend(); ++it) {
//			cout << *it << "\n";
			ListNode *node = new ListNode(*it);
			this->AddFromHead(node);
		}
	}

	void Clear() {
		ListNode *prev;
		ListNode *curr = head_;
		while (curr) {
			prev = curr;
			curr = curr->next_;
			delete prev;
		}
		head_ = NULL;
	}

	void Print() {
		ListNode *tmp = head_;
		cout << "List: ";
		while (tmp) {
			cout << tmp->value_ << " ";
			tmp = tmp->next_;
		}
		cout << "\n";
	}

	ListNode* FindMidPoint() {
		ListNode *chaser = NULL;
		ListNode *runner = NULL;

		assert(!head_);

		chaser = head_;
		runner = head_->next_;

		while (runner != NULL && runner->next_ != NULL) {
			chaser = chaser->next_;
			runner = runner->next_;
			runner = runner->next_;
		}

		return chaser;
	}

	~List() {
		Clear();
	}
};

TEST(FindMidPoint, case1) {
	vector<int> nodes_value{5};

	List list;
	list.Clear();
	list.Construct(vector<int>{5});
	ASSERT_EQ(5, list.FindMidPoint()->value_);

	list.Clear();
	list.Construct(vector<int>{5, 3});
	ASSERT_EQ(5, list.FindMidPoint()->value_);

	list.Clear();
	list.Construct(vector<int>{5, 3, 4});
	ASSERT_EQ(3, list.FindMidPoint()->value_);

	list.Clear();
	list.Construct(vector<int>{5, 3, 4, 1});
	ASSERT_EQ(3, list.FindMidPoint()->value_);

	list.Clear();
	ASSERT_EQ(NULL, list.FindMidPoint());
//	ASSERT_STREQ(" , . edcba  dac ", str);
}



