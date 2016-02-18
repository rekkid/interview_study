/*
 * 5_6_reverse_linked_list.cc
 *
 * Reverse the linked listand return the new head.
 * 将链表逆转并且返回新的链表头
 *
 * A linked list can be reversed either iteratively or recursively.
 * Could you implement both?
 *
 *  Created on: Feb 10, 2016
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

	// 算法没有考虑旋转，即k可能大于链表的长度
	static ListNode* RotateRight1(ListNode *head, int k) {
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

	list.head_ = ListNode::ReverseList(list.head_);
	cout << "After reverse list\n";
	list.Print();
}

TEST(RotateRight, case2) {
	List list;
	list.Clear();
	vector<int> nodes{1, 2};
	list.Construct(nodes);
	list.Print();

	list.head_ = ListNode::ReverseList(list.head_);
	cout << "After reverse list\n";
	list.Print();
}

TEST(RotateRight, case3) {
	List list;
	list.Clear();
	vector<int> nodes{1};
	list.Construct(nodes);
	list.Print();

	list.head_ = ListNode::ReverseList(list.head_);
	cout << "After reverse list\n";
	list.Print();
}
