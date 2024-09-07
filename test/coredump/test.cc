// 给定一个长度为S的链表:
// N(0) -> N(1) -> N(2) -> … -> N(s-2) -> N(s-1) 
// 将链表原地调整为以下顺序：
// N(0) -> N(s-1) -> N(1) -> N(s-2) -> …. N(s/2-1) -> N(s/2) s 为偶数1,2,3,4,5,6,7,8,9,10 =>1,10,2,9,3,8,4,7,5,6
// N(0) -> N(s-1) -> N(1) -> N(s-2) -> … N(s/2) s 为奇数 1,2,3,4,5,6,7,8,9=>1,9,2,8,3,7,4,6,5
// 要求实现函数：
#include <iostream>


struct Node{
    int data;
    Node *next;
    Node(int data_, Node* next_):data(data_),next(next_){}
};

void ResortNodeList(struct Node* root) {
    if (root == nullptr) return ;
    int size = 0;
    Node* tmp = root;
    while(tmp != nullptr) {
        size++;
        tmp = tmp->next;
    }

    int mid = size/2+1;
    size = 0;
    Node* node_tmp = root;
    Node* node_tmp_null = nullptr;
    while(node_tmp != nullptr) {
        if (++size == mid) {
            break;
        }
        if (size == mid-1) {
            node_tmp_null = node_tmp;
        }
        node_tmp = node_tmp->next;

    }
    node_tmp_null->next = nullptr;

    
    //reverse     nullptr->node1->node2->node3->node4
    Node* pre = nullptr;
    Node* cur = node_tmp;

    while (cur != nullptr) {
        Node* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    //combine
    tmp = root;
    Node* pp = nullptr;//1,  2,  3, 4, 5
    Node* pt = nullptr;//  10,  9, 8, 7, 6
    while(pre && tmp) {
        Node* tmp_next = tmp->next; 
        tmp->next = pre;  
        pp = pre;
        pt = tmp;
        Node* pre_next = pre->next; 
        pre->next = tmp_next;
        pre = pre_next;          
        tmp = tmp_next;
    }

    if(pre) {
        pp->next = pre;
    }
    if (tmp) {
        pt->next = tmp;
    }
}


int main() {
    Node* node10 = {new Node(10,nullptr)};
    Node* node9 = {new Node(9,node10)};
    Node* node8 = {new Node(8,node9)};
    Node* node7 = {new Node(7,node8)};
    Node* node6 = {new Node(6,node7)};
    Node* node5 = {new Node(5,node6)};
    Node* node4 = {new Node(4,node5)};
    Node* node3 = {new Node(3,node4)};
    Node* node2 = {new Node(2,node3)};
    Node* node1 = {new Node(1,node2)};

    ResortNodeList(node1);
    // ResortNodeList(node2);
    return 0;
}
