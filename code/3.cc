#include <iostream>
#include <set>

int minnum(std::string& str) {
    int l = 0,r = 0;
    int ans = 0;
    std::set<char> sets;
    for (;r < str.size(); ++r) {
        while (sets.count(str[r]) && str[l] != str[r]) {
            sets.erase(l++);
        }
        ans = std::max(ans,r-l+1);
        sets.insert(str[r]);
    }
    return ans;
}

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

ListNode* mergeList(ListNode* list1, ListNode* list2) {
    if(!list1) return list2;
    if(!list2) return list2;
    if (list1->val > list2->val) {
        list2->next = mergeList(list1,list2->next);
    } else {
        list1->next = mergeList(list1->next,list2);
    }
}

ListNode* mergeList1(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode();
    auto tmp = dummy;
    while(list1 && list2) {
        if(list1->val < list2->val) {
            tmp->next = list1;
            list1 = list1->next;
        } else {
            tmp->next = list2;
            list2 = list2->next;
        }
        tmp = tmp->next;
    }

    return dummy->next;
}

int main() {

    return 0;
}
