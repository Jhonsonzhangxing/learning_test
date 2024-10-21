#include<iostream>

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == nullptr) return head;
    ListNode* pre;
    for (int i = 0; i < left -1; ++i) {
        pre = head->next;
    }
    auto p = pre, q = pre->next;
    auto cur = pre->next;

    for (int i = 0; i < right - left +1; ++i) {
        auto t = cur->next;
        cur->next = pre;
        pre = cur;
        cur = t;
    }
    p->next = pre;
    q->next = cur;

    return dummy->next;
}

int main() {
    ListNode node5(5);
    ListNode node4(4,&node5);
    ListNode node3(3,&node4);
    ListNode node2(2,&node3);
    ListNode node1(1,&node2);

    reverseBetween(&node1,2,4);
    
    return 0;

}