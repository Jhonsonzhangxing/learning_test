#include <atomic>
#include <memory>
#include <iostream>

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
    }

    std::shared_ptr<T> dequeue() {
        Node* old_head = head.load();

        while (old_head == tail.load() || !head.compare_exchange_weak(old_head, old_head->next.load())) {
            old_head = head.load();
        }

        return old_head->next.load()->data;
    }
};

int main() {
    LockFreeQueue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << *queue.dequeue() << std::endl; // 1
    std::cout << *queue.dequeue() << std::endl; // 2
    std::cout << *queue.dequeue() << std::endl; // 3

    return 0;
}