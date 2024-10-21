#include<iostream>
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* deletenode(ListNode* head, int N) {
    ListNode*  dummy = new ListNode(0,head);
    ListNode* fast = dummy;
    ListNode* slow = dummy;
    
    for (int i = 0; i < N; ++i) {
        fast = fast->next;
    }

    while(fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return dummy->next;
}

int main() {

    return 0;
}