#include<iostream>

template<typename T>
class Stack {
    struct Node {
        T data_;
        Node* next_;
        Node(const T& data):data_(data) {
            this->next_ = nullptr;
        }
    };

    Node* head_;

public:
    Stack(){
        head = new Node<T>();
    }

    void push (const T& data) {
        Node* new_node = new Node<T>()
        new_node->next = head_;
        head_ = new_node;
    }

    void pop() {
        if (head_) {
            auto tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
    }
};


template<typename T>
class stacks {
    struct Node {
        std::shared_ptr<T> data_;
        std::atomic<Node*> next_;
        Node(const T& data):data_(std::make_shared<T>(data)) {
            this->next_ = nullptr;
        }
    };
    std::atomic<Node*> head_;
public:
    void push(const T& data) {
        auto new_node = new Node(data);
        new_node->next = head_.load();
         while(!head_.compare_exchange_weak(new_node->next,new_node)){}
    }
};
