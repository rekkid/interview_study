/*
 * 3_10_add_list.cc
 *
 * Given two linked lists, each element of the lists is a
 * integer. Write a function to return a new list, which is
 * the "sum" of the given two lists.
 *
 * Part a. Given input (7->1->6) + (5->9->2), output 2->1->9.
 * Part b. Given input (6->1->7) + (2->9->5), output 9->1->2.
 *
 * 给定两个链表，链表的每个元素都是一个整数。编写一个函数来返回一个新的
 * 链表，它是给定的两个链表的“和”。
 * Part a，给定输入(7->1->6) + (5->9->2)，输入2->1->9，即617 + 295 = 912
 * Part b，给定输入(6->1->7) + (2->9->5)，输出9->1->2，即617 + 295 = 912
 *
 *  Created on: Feb 13, 2016
 *      Author: ZJ
 */

#include <vector>
#include <string>
#include "gtest/gtest.h"

using namespace std;

class ListNode;

struct ListWithCarry {
	ListNode *head;
	int carry;
};



class ListNode {
public:
	int value_;
	ListNode *next_;
public:
	ListNode(int value) :
			value_(value), next_(NULL) {
	}

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
		if (head == NULL)
			return NULL;
		if (head->next_ == NULL)
			return head;

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
		if (head == NULL)
			return;
		ReversedTraverse(head->next_);
		cout << head->value_ << " ";
	}

	static ListNode *AddListA(ListNode *l1, ListNode *l2) {
		ListNode *dummy = new ListNode(0);
		ListNode *curr = dummy;

		int carry = 0;
		while (l1 && l2) {
			int s = l1->value_ + l2->value_ + carry;
			if (s >= 10) {
				carry = 1;
				s = s - 10;
			} else {
				carry = 0;
			}
			ListNode *node = new ListNode(0);
			node->value_ = s;
			curr->next_ = node;
			curr = curr->next_;
			l1 = l1->next_;
			l2 = l2->next_;
		}
		ListNode *l = NULL;
		if (l1) {
			l = l1;
		} else {
			l = l2;
		}
		while (l) {
			int s = l->value_ + carry;
			if (s >= 10) {
				carry = 1;
				s = s - 10;
			} else {
				carry = 0;
			}
			ListNode *node = new ListNode(0);
			node->value_ = s;
			curr->next_ = node;
			curr = curr->next_;
			l = l->next_;
		}
		if (carry == 1) {
			ListNode *node = new ListNode(0);
			node->value_ = carry;
			curr->next_ = node;
		}
		ListNode *new_head = dummy->next_;
		delete dummy;
		return new_head;
	}

	static int GetListLen(ListNode *head) {
		int len = 0;

		while (head) {
			len++;
			head = head->next_;
		}
		return len;
	}

	static ListNode* PadList(ListNode *head, int diff) {
		ListNode *dummy = new ListNode(0);
		ListNode *curr = dummy;
		ListNode *new_head = NULL;

		for (int i = 0; i < diff; ++i) {
			ListNode *node = new ListNode(0);
			curr->next_ = node;
			curr = curr->next_;
		}
		curr->next_ = head;

		new_head = dummy->next_;
		delete dummy;
		return new_head;
	}

	static ListNode *AddListWithCarry(ListNode *l1, ListNode *l2, int &carry) {
		ListNode *dummy = new ListNode(0);
		ListNode *curr = dummy;

		carry = 0;
		if (l1 == NULL && l2 == NULL)
			return NULL;

		ListNode *l = AddListWithCarry(l1->next_, l2->next_, carry);

		ListNode *node = new ListNode(0);

		int sum = l1->value_ + l2->value_ + carry;

		carry = sum / 10;
		node->value_ = sum % 10;
		node->next_ = l;
		curr->next_ = node;

		ListNode *new_head = dummy->next_;
		delete dummy;
		return new_head;
	}

	// 困难，参考P62解答；需要考虑两个链表长度不等的情况
	static ListNode *AddListB(ListNode *l1, ListNode *l2) {
		ListNode *dummy = new ListNode(0);
		ListNode *curr = dummy;

		if (l1 == NULL && l2 == NULL)
			return NULL;
		if (l1 == NULL)
			return l2;
		if (l2 == NULL)
			return l1;

		int len1 = GetListLen(l1);
		int len2 = GetListLen(l2);
		if (len1 < len2) {
			l1 = PadList(l1, len2 - len1);
		} else if (len1 > len2) {
			l2 = PadList(l2, len1 - len2);
		}

		int carry = 0;
		ListNode *l = AddListWithCarry(l1, l2, carry);

		if (l == NULL) {
			ListNode *node = new ListNode(0);
			node->value_ = carry;
			curr->next_ = node;
		} else {
			if (carry != 0) {
				ListNode *node = new ListNode(0);
				node->value_ = carry;
				node->next_ = l;
				curr->next_ = node;
			} else {
				curr->next_ = l;
			}
		}

		ListNode *new_head = dummy->next_;
		delete dummy;
		return new_head;
	}
};

class List {
public:
	ListNode *head_;
public:
	List() :
			head_(NULL) {
	}
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

TEST(AddListA, case1) {
	List l1;
	l1.Clear();
	vector<int> nodes1 { 7, 1, 6 };
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 { 5, 9, 2 };
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part a: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListA(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListA, case2) {
	List l1;
	l1.Clear();
	vector<int> nodes1 { 2 };
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 { 9, 9, 9 };
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part a: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListA(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListA, case3) {
	List l1;
	l1.Clear();
	vector<int> nodes1 { };
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 { };
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part a: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListA(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListB, case1) {
	List l1;
	l1.Clear();
	vector<int> nodes1 {7};
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 {5};
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part b: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListB(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListB, case2) {
	List l1;
	l1.Clear();
	vector<int> nodes1 {6, 1, 7};
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 {2, 9, 5};
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part b: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListB(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListB, case3) {
	List l1;
	l1.Clear();
	vector<int> nodes1 {1, 7};
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 {2, 9, 5};
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part b: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListB(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListB, case4) {
	List l1;
	l1.Clear();
	vector<int> nodes1 {1};
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 {0};
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part b: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListB(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}

TEST(AddListB, case5) {
	List l1;
	l1.Clear();
	vector<int> nodes1 {1};
	l1.Construct(nodes1);
	l1.Print();

	List l2;
	l2.Clear();
	vector<int> nodes2 {9, 9, 9};
	l2.Construct(nodes2);
	l2.Print();

	cout << "Part b: add l1 and l2:\n";
	List result;
	result.head_ = ListNode::AddListB(l1.head_, l2.head_);
	result.Print();
	cout << "\n";
}
