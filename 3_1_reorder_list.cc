/*
 * 3_1_reorder_list.cc
 *
 * Given a linked list and a value x, write a function to reorder
 * this list such that all nodes less than x come before the nodes
 * greater than or equal to x.
 *
 *  Created on: Jan 28, 2016
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
	void Add(ListNode* node) {
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
			this->Add(node);
		}
	}

	void Delete() {
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

	void ReorderList(int x) {
		ListNode *low_dummy = new ListNode(0);
		ListNode *low_curr = low_dummy;

		ListNode *high_dummy = new ListNode(0);
		ListNode *high_curr = high_dummy;

		while(head_) {
			ListNode *tmp = head_->next_;
			head_->next_ = NULL;
			if (head_->value_ >= x) {
				high_curr->next_ = head_;
				high_curr = head_;
			} else {
				low_curr->next_ = head_;
				low_curr = head_;
			}
			head_ = tmp;
		}

		low_curr->next_ = high_dummy->next_;
		head_ = low_dummy->next_;

		delete low_dummy;
		delete high_dummy;
	}

	~List() {
		Delete();
	}
};

ListNode* ReorderList(ListNode *head, int x) {
	if (head == NULL) {
		return head;
	}
	if (head->next_ == NULL) {
		return head;
	}

	ListNode *prev = head;
	ListNode *cur = head->next_;

	while (cur) {
//		cout << cur->value_ << "\n";
		if (cur->value_ < x) {
			prev->next_ = cur->next_;
			cur->next_ = head;
			head = cur;
		} else if (cur->value_ == x) {
			if (head->value_ >= cur->value_) {
				prev->next_ = cur->next_;
				cur->next_ = head;
				head = cur;
			} else {
				prev = cur;
			}
		} else {
			prev = prev->next_;
		}
		cur = prev->next_;
	}

	return head;
}

TEST(ReorderList, case1) {
	vector<int> nodes_value = {5, 3, 4, 1, 6, 1, 6};


/*	for (int i : nodes_value) {
		list.head_ = ReorderList(list.head_, i);
		cout << "after reorder_list by " << i << "\n";
		list.Print();
		list.Delete();
		list.Construct(nodes_value);
	}*/

	vector<int> values = {5, 3, 4, 1, 6, -1, 8};
	for (int i : values) {
		List list;
		list.Construct(nodes_value);
		list.Print();
		list.ReorderList(i);
		cout << "after reorder_list by " << i << "\n";
		list.Print();
		cout << "\n";
	}


//	ASSERT_STREQ(" , . edcba  dac ", str);
}
