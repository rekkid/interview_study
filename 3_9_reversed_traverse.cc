/*
 * 3_9_reversed_traverse.cc
 *
 * Traverse the linked list reversely.
 * 倒序地访问链表。
 *
 *  Created on: Feb 13, 2016
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

	// Remove the nth node to end.
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
		if (!head) {
			return NULL;
		}
		ListNode *chaser;
		ListNode *runner;

		chaser = head;
		runner = head;

		while (runner && runner->next_) {
			runner = runner->next_->next_;
			chaser = chaser->next_;
			if (chaser == runner) {
				break;
			}
		}
		if (!runner || !runner->next_) {
			return NULL;
		}

		cout << "Find a loop\n";

		chaser = head;
		while (chaser != runner) {
			chaser = chaser->next_;
			runner = runner->next_;

		}

		return chaser;
	}

	// 考虑旋转情况
	static ListNode* RotateRight(ListNode *head, int k) {
		if (!head || k < 0) {
			return NULL;
		}

		int len = 1;
		ListNode *tmp = head;
		while (tmp->next_) {
			len++;
			tmp = tmp->next_;
		}
		tmp->next_ = head;

		cout << "len: " << len << "\n";

		int pos = k % len;

		ListNode *cur = head;
		for (int i = 0; i < len - pos - 1; ++i) {
			cur = cur->next_;
		}
		ListNode *new_head = cur->next_;
		cur->next_ = NULL;

		return new_head;
	}

	// Reverse list
	static ListNode* ReverseList1(ListNode *head) {
		if (head == NULL) return NULL;
		if (head->next_ == NULL) return head;

		ListNode *prev = head;
		ListNode *curr = head->next_;

		while (curr != NULL) {
			prev->next_ = curr->next_;
			curr->next_ = head;
			head = curr;
			curr = prev->next_;
		}

		return head;
	}

	static ListNode *ReverseList(ListNode *head) {
		ListNode *prev = NULL;
		ListNode *next = NULL;

		while (head) {
			next = head->next_;
			head->next_ = prev;

			prev = head;
			head = next;
		}

		return prev;
	}

	static void ReversedTraverse(ListNode *head) {
		if (head == NULL) return;
		ReversedTraverse(head->next_);
		cout << head->value_ << " ";
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

TEST(ReversedTraverse, case1) {
	List list;
	list.Clear();
	vector<int> nodes{1, 2, 3, 4, 5};
	list.Construct(nodes);
	list.Print();

	cout << "Traverse linked list reversely.\n";
	ListNode::ReversedTraverse(list.head_);
	cout << "\n";
}

TEST(ReversedTraverse, case2) {
	List list;
	list.Clear();
	vector<int> nodes{1};
	list.Construct(nodes);
	list.Print();

	cout << "Traverse linked list reversely.\n";
	ListNode::ReversedTraverse(list.head_);
	cout << "\n";
}

TEST(ReversedTraverse, case3) {
	List list;
	list.Clear();
	vector<int> nodes{};
	list.Construct(nodes);
	list.Print();

	cout << "Traverse linked list reversely.\n";
	ListNode::ReversedTraverse(list.head_);
	cout << "\n";
}

