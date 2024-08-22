#include <iostream>
#include <atomic>

// template<typename T>
// struct Node {   
//     T data;
//     Node* next;
//     Node(const T& data) : data(data), next(nullptr) {}
// };

// template<typename T>
// class stack {
//     std::atomic<Node<T>*> head;
// public:
//     void push(const T& data) {
//         Node<T>* new_node = new Node<T>(data);
//         new_node->next = head.load(std::memory_order_relaxed);
//         while(!head.compare_exchange_weak(new_node->next, new_node,std::memory_order_release,std::memory_order_relaxed))
//             ;
//     }

//     void pop() {
//         Node<T>* old_head = head.load(std::memory_order_relaxed);
//         while(!head.compare_exchang_weak(old_head, head.next))
//             ;
//         delete old_head;
//     }
// };

template <typename T>
class stackfree {
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;
        Node(T value):data(std::make_shared<T>(T(value))),next(nullptr) {}
    };

    std::atomic<Node*> head;
public:
    stackfree():head(nullptr){}

    void push(T value) {
        Node* new_node = new Node(value);
        new_node->next = head.load();
        while(!head.compare_exchange_weak( new_node->next,new_node))
            ;
        
    }
};