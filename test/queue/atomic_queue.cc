#include <atomic>
#include <memory>
#include <iostream>
#include <thread>
#include <vector>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;

        Node(T value) : data(std::make_shared<T>(value)), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    std::atomic<int> count{0};
public:
    LockFreeQueue() {
        Node* dummy = new Node(T());
        head.store(dummy);
        tail.store(dummy);
    }

    ~LockFreeQueue() {
        while (Node* old_head = head.load()) {
            head.store(old_head->next);
            delete old_head;
        }
    }

    void enqueue(T value) {
        Node* new_node = new Node(value);
        Node* old_tail = tail.load();

        while (!tail.compare_exchange_weak(old_tail, new_node)) {
            old_tail = tail.load();
        }

        old_tail->next.store(new_node);
        count.fetch_add(1);
        // std::cout << "count: " << std::atomic_fetch_add(&count, 1)<< std::endl;
    }

    std::shared_ptr<T> dequeue() {
        Node* old_head = head.load();

        while (old_head == tail.load() || !head.compare_exchange_weak(old_head, old_head->next.load())) {
            old_head = head.load();
        }
        count.fetch_sub(1);

        return old_head->next.load()->data;
    }

    int get_count() {
        return (int)count.load();
    }
};

LockFreeQueue<int> queue;

void fun(int i) {
    queue.enqueue(i*i);
    queue.enqueue(2*i*i);
    queue.enqueue(3*i*i);
    
    // std::cout << "(i: " << i << ",i*i: " << i*i << ",2*i*i: " << 2*i*i << ", 3*i*i: " << 3*i*i << ")"<< std::endl;
}

void fun2(int i) {
    std::cout << "reader: " << i << " : "<< *queue.dequeue() << std::endl;
    // std::cout << "(i: " << i << ",i*i: " << i*i << ",2*i*i: " << 2*i*i << ", 3*i*i: " << 3*i*i << ")"<< std::endl;
}

int main() {
    std::vector<std::thread> v;
    for (int i = 1; i < 5; ++i) {
        v.emplace_back(fun,i);
    }
    // std::cout << queue.get_count()  << ", test before"<< std::endl;
    // std
    for (int i = 1; i <= 12; ++i) {
        v.emplace_back(fun2,i);
    }

    for (auto& t : v)
        t.join();
    std::cout << queue.get_count()  << ", test after" << std::endl;
    return 0;
}

// #include <atomic>
// #include <vector>
// #include <memory>
// #include <iostream>
// #include <thread>

// template <typename T>
// class queue1 {
//     struct Node {
//         std::shared_ptr<T> value;
//         std::atomic<Node*> next;
//         Node(T value):value(std::make_shared<T>(value)),next(nullptr) {}

//     };
//     std::atomic<Node*> head;
//     std::atomic<Node*> tail;
// public:
//     queue1() {
//         Node* dummy = new Node(T());
//         head.store(dummy);
//         tail.store(dummy);
//     }
//     ~queue1() {
//         while(Node* old_head = head.load()) {
//             head.store(old_head->next);
//             delete old_head;
//         }
//     }

//     void enqueue (T value) {
//         Node* new_node = new Node(T(value));
//         Node* old_node = tail.load();
//         while(!tail.compare_exchange_weak(old_node, new_node)) {
//             old_node = tail.load();
//         }
//         old_node->next.store(new_node);
//     }

//     std::shared_ptr<T> dequeue() {
//         Node* old_head = head.load();
//         while(old_head == tail.load() || !head.compare_exchange_weak(old_head, old_head->next.load())) {
//             old_head = head.load();
//         }

//         // return old_head.load();
//         return old_head->next.load()->value;
//     }

// };

// queue1<int> queue;

// void fun(int i) {
//     queue.enqueue(i*i);
//     queue.enqueue(2*i*i);
//     queue.enqueue(3*i*i);
    
//     // std::cout << "(i: " << i << ",i*i: " << i*i << ",2*i*i: " << 2*i*i << ", 3*i*i: " << 3*i*i << ")"<< std::endl;
// }

// void fun2(int i) {
//     std::cout << "reader: " << i << " : "<< *queue.dequeue() << std::endl;
//     // std::cout << "(i: " << i << ",i*i: " << i*i << ",2*i*i: " << 2*i*i << ", 3*i*i: " << 3*i*i << ")"<< std::endl;
// }

// int main() {
//     std::vector<std::thread> v;
//     for (int i = 1; i < 5; ++i) {
//         v.emplace_back(fun,i);
//     }
//     // std::cout << queue.get_count()  << ", test before"<< std::endl;
//     // std
//     for (int i = 1; i <= 12; ++i) {
//         v.emplace_back(fun2,i);
//     }

//     for (auto& t : v)
//         t.join();
//     // std::cout << queue.get_count()  << ", test after" << std::endl;
//     return 0;
// }