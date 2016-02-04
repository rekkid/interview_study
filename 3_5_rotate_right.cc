/*
 * 3_5_rotate_right.cc
 *
 * Given a list, rotate the list to the right by k places, where k
 * is non-negative. e.g: 1->2->3->4->5, k = 2; after rotation：
 * 4->5->1->2->3
 *
 * 给定一个链表，向右旋转链表k个位置，其中k是一个非负数。例如， 1->2->3->4->5, k = 2;
 * 旋转之后得到： 4->5->1->2->3。
 *
 *  Created on: Feb 3, 2016
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

	static ListNode* RotateRight(ListNode *head, int k) {
		ListNode *slow = head;
		ListNode *fast = head;

		int i = 0;
		while (fast && i < k - 1) {
			fast = fast->next_;
			i++;
		}
		if (!fast)
			return NULL;

		while (fast->next_) {
			slow = slow->next_;
			fast = fast->next_;
		}

		if (head == slow) {
			return head;
		}

		ListNode *prev = head;
		while (prev->next_ != slow) {
			prev = prev->next_;
		}
		prev->next_ = NULL;
		fast->next_ = head;
		return slow;
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

TEST(RotateRight, case1) {
	List list;
	list.Clear();
	vector<int> nodes{1, 2, 3, 4, 5};
	list.Construct(nodes);
	list.Print();

	list.head_ = ListNode::RotateRight(list.head_, 2);
	cout << "After rotate right by 2 \n";
	list.Print();
}

TEST(RotateRight, case2) {
	List list;
	list.Clear();
	vector<int> nodes{1, 2, 3, 4, 5};

	for (int i : nodes) {
		list.Clear();
		list.Construct(nodes);
		list.Print();
		list.head_ = ListNode::RotateRight(list.head_, i);
		cout << "After rotate right by " << i << " \n";
		list.Print();
		cout << "\n";
	}

}

TEST(RotateRight, case3) {
	List list;
	list.Clear();
	vector<int> nodes{1, 2, 3, 4, 5};

	vector<int> nodes2{0, 1, 2, 3, 4, 5, 6, 7};
	for (int i : nodes2) {
		list.Clear();
		list.Construct(nodes);
		list.Print();
		list.head_ = ListNode::RotateRight(list.head_, i);
		cout << "After rotate right by " << i << " \n";
		list.Print();
		cout << "\n";
	}

}
