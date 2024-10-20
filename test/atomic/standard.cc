#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

template<typename T>
struct Node {
    T data;
    // Node* next;
    std::shared_ptr<Node<T>> next;
    Node(const T& data):data(data),next(nullptr){}
};

template<typename T>
class Stack {
    // std::atomic<Node<T>*> head;
    std::atomic<std::shared_ptr<Node<T>>> head;
public:

    void push(const T& data) {
        // Node<T>* new_node = new Node<T>(data);
        auto new_node = std::make_shared<Node<T>>(data);
        new_node->next = head.load(std::memory_order_relaxed);
        while(!std::atomic_compare_exchange_weak_explicit(&head,&new_node->next,new_node,std::memory_order_release,std::memory_order_relaxed));
        std::cout <<"input: " << data << std::endl;
    }

    Node<T>* pop () {
        auto node = head.load(std::memory_order_release);
        if(node == nullptr) return nullptr;
        while(!std::atomic_compare_exchange_weak_explicit(&head,&node,node->next,std::memory_order_release, std::memory_order_relaxed));
        return node;
    }
};

Stack<int> stacks;

// template<typename T>
void stack_push(int num) {
    for (int i = 1; i <= 3; ++i) {
        stacks.push(i*i*num);
    }
}

// template<typename T>
void stack_pop() {
    while(true) {
        auto ptr = stacks.pop();
        if (ptr != nullptr) {
            std::cout << ptr->data << std::endl;
            // delete ptr;
        } else {

        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::atomic<bool> lock_ex(false);
int new_line{1};
void exchange(int n) {
    for (int i = 0; i < 3; ++i) {
        while (std::atomic_exchange_explicit(&lock_ex, true, std::memory_order_acquire)) {
            ;
        }
        std::cout << n << ", " << lock_ex.load() << std::endl;
        std::atomic_store_explicit(&lock_ex, false, std::memory_order_release);
    }
}

std::atomic<int> cnt;
void sub(int id) {
    for (;;) {
        int idx = std::atomic_fetch_sub_explicit(&cnt, 1, std::memory_order_acquire);
        if (idx >= 0) {
            std::cout << "reader: " << std::to_string(id)  << ", cnt: " << idx << std::endl;
        } else {
            std::cout << "reader: " << std::to_string(id) << " done " << std::endl;
            break;
        }
    }
}

std::atomic_flag lock = ATOMIC_FLAG_INIT;
void f(int n) {
    for (int cnt = 0; cnt < 40; ++cnt) {
        while(lock.test_and_set(std::memory_order_acquire)) {
            // std::cout << "thread: " << pthread_self() << ", wait: " << std::endl;
        }
        static int out;
        // std::cout << n << ((++out % 40) == 0 ? '\n' : ' ');
        if (cnt == 39) {
            std::cout << "thread: " << pthread_self() << std::endl;
        }
        
        lock.clear(std::memory_order_release);
    }
}


int main() {
    std::vector<std::thread> v_in;
    std::vector<std::thread> v_out;
    cnt = 10;
    for (int n = 1; n <= 5; ++n) {
        // v.emplace_back(f,n);
        // v.emplace_back(sub,n);
        // v.emplace_back(exchange,n);
        // stack_push(n);
        v_in.emplace_back(stack_push,n);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        v_out.emplace_back(stack_pop);
    }

    for (auto& t : v_in) {
        t.join();
    }

    for (auto& t : v_out) {
        t.join();
    }

    return 0;
}
// https://zhuanlan.zhihu.com/p/720226018