#include <iostream>
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void deldup(ListNode* head) {
    ListNode* dummy = new ListNode(0,head);
    auto pre = dummy;
    auto cur = head;
    while(cur) {
        while(cur->next && cur->next->val == cur->val){
            cur = cur->next;
        }
        if (pre->next == cur) {
            pre = cur;
        } else {
            pre->next = cur;
        }
        cur = cur->next;
    }
}


int main() {

    return 0;
}