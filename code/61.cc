#include<iostream>
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void flip(ListNode* head, int k) {
    if (!head ||  !head->next) return;
    int n = 0;
    auto tmp = head;
    while(tmp) {
        n++;
        tmp = tmp->next;
    }

    auto fast = head,slow = head;
    while(k--) {
        fast = fast->next;
    }

    while(fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    auto ans = slow->next;
    slow->next = nullptr;
    fast->next = head;

}

int main() {
    return 0;
}
