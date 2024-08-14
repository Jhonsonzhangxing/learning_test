#include <atomic>

template<typename T>
struct node {
    T data;
    node* next;
    node(const T& data) : data(data),next(nullptr) {}
};

template<class T>
class stack {
    std::atomic<node<T>*> head;
public:
    void push(const T& data) {
        node<T>* new_node = new node<T>(data);
        new_node->next = head.load(std::memory_order_relaxed);
        while(!std::atomic_compare_exchange_weak_explicit(&head,&new_node->next, new_node, std::memory_order_release,std::memory_order_relaxed));
    }

    bool pop() {
        bool ret = false;
        do {
            node<T>* old_data = *head.load(std::memory_order_release);
        } while(!std::atomic_compare_exchange_weak_explicit(&head,old_data,head->next,std::memory_order_release,std::memory_order_relaxed)){

        }
    }

};