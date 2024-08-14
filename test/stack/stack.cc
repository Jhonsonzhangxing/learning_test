#include <iostream>
#include <atomic>

template<typename T>
struct Node {   
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class stack {
    std::atomic<Node<T>*> head;
public:
    void push(const T& data) {
        Node<T>* new_node = new Node<T>();
        new_node->next = head.load(std::memory_order_relaxed);
        while(!head.compare_exchange_weak(new_node->next, new_node,std::memory_order_release,std::memory_order_relaxed));
    }

    void pop() {
        Node<T>* old_head = head.load(std::memory_order_relaxed);
        while(!head.compare_exchang_weak(old_head, head.next))
            ;
        delete old_head;
    }
};