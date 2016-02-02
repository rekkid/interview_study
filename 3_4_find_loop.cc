/*
 * 3_4_find_loop.cc
 *
 * Given a linked list that may contain a circle, write a function
 * to return the node at the beginning of that circle. Return NULL
 * if such list dosen't contain a circle.
 *
 * 给定一个可能包含一个环的链表，编写一个函数来返回环开始的节点。
 * 如果该链表不包含环，返回NULL。
 *
 *  Created on: Jan 31, 2016
 *      Author: ZJ
 */

#include <vector>
#include <string>
#include "gtest/gtest.h"

using namespace std;

class ListNode {
public:
	int value_;
	ListNode *next_;
public:
	ListNode(int value) : value_(value), next_(NULL) {}

	ListNode* RemoveNthFromEnd(ListNode* head, int n) {
		if (n <= 0)
			return head;

		if (!head)
			return NULL;

		ListNode *runner = head;
		for (int i = 0; i < n - 1; ++i) {
			runner = runner->next_;
			if (!runner) {
				return head;
			}
		}

		ListNode *chaser = head;
		ListNode *prev = NULL;
		while (runner->next_) {
			prev = chaser;
			chaser = chaser->next_;
			runner = runner->next_;
		}

		// Find chaser to delete
		if (!prev) {
			head = chaser->next_;
			delete chaser;
		} else {
			prev->next_ = chaser->next_;
			delete chaser;
		}
		return head;
	}

	ListNode* FindLoop(ListNode* head) {
		ListNode *chaser;
		ListNode *runner;

		if (!head || !head->next_) {
			return NULL;
		}
		chaser = head;
		runner = head->next_;
		int n = 1;
		int m = 1;
		bool is_loop = false;

		while (runner) {
			m++;
			if (chaser == runner) {
				is_loop = true;
				break;
			}
			if (!runner->next_) {
				is_loop = false;
				break;
			} else {
				runner = runner->next_;
				m++;
				runner = runner->next_;
				chaser = chaser->next_;
				n++;
			}
		}
		if (!is_loop) {
			return NULL;
		}

		int loop_len = m - n;

		cout << "n: " << n << ", m:" << m << ", loop_len: " << loop_len << "\n";

		ListNode *loop_start = runner;
		for (int i = 0; i < loop_len / 2 + 1; ++i) {
			loop_start = loop_start->next_;
		}
		return loop_start;

	}
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

	void RemoveNthFromEnd(int n) {
		if (head_) {
			head_ = head_->RemoveNthFromEnd(head_, n);
		}
	}

	~List() {
//		Clear();
	}
};

TEST(FindLoop, case1) {
	List list;
	list.Clear();
	list.Construct(vector<int>{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
	list.Print();

	ListNode *node_end = list.head_;
	for (int i = 0; i < 13 - 1; ++i) {
		node_end = node_end->next_;
	}
	cout << "node_end: " << node_end << ", value: " << node_end->value_ << ", " << node_end->next_ << "\n";

	ListNode *node_intersection = list.head_;
	for (int i = 0; i < 5 - 1; ++i) {
		node_intersection = node_intersection->next_;
	}
	cout << "node_intersection: " << node_intersection << ", value: " << node_intersection->value_ << "\n";

	cout << "node_end->next_: " << node_end->next_ << "\n";
	node_end->next_ = node_intersection;



	ListNode *node = list.head_;

	for (int i = 0; i < 100; ++i) {
		cout << node->value_ << ", ";
		node = node->next_;
	}

	ListNode *mid = list.head_->FindLoop(list.head_);
	if (mid) {
		cout << "Find loop, start is " << mid << ", value: " << mid->value_ << "\n";
	} else {
		cout << "Do not find loop \n";
	}
}

TEST(FindLoop, case2) {
	List list;
	list.Clear();
	list.Construct(vector<int>{-1, 0, 1, 2, 3, 4, 5, 6});
	list.Print();

	ListNode *node_end = list.head_;
	for (int i = 0; i < 8 - 1; ++i) {
		node_end = node_end->next_;
	}
	cout << "node_end: " << node_end << ", value: " << node_end->value_ << ", " << node_end->next_ << "\n";

	ListNode *node_intersection = list.head_;
	for (int i = 0; i < 5 - 1; ++i) {
		node_intersection = node_intersection->next_;
	}
	cout << "node_intersection: " << node_intersection << ", value: " << node_intersection->value_ << "\n";

	cout << "node_end->next_: " << node_end->next_ << "\n";
	node_end->next_ = node_intersection;

	ListNode *node = list.head_;

	for (int i = 0; i < 100; ++i) {
		cout << node->value_ << ", ";
		node = node->next_;
	}

	ListNode *mid = list.head_->FindLoop(list.head_);
	if (mid) {
		cout << "Find loop, start is " << mid << ", value: " << mid->value_ << "\n";
	} else {
		cout << "Do not find loop \n";
	}

}


