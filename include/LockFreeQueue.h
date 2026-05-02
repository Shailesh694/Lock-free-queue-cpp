#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include <atomic>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;

        Node(T value) : data(value), next(nullptr) {}
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
        while (Node* old = head.load()) {
            head.store(old->next);
            delete old;
        }
    }

    void push(T value) {
        Node* newNode = new Node(value);

        while (true) {
            Node* last = tail.load();
            Node* next = last->next.load();

            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_weak(next, newNode)) {
                        tail.compare_exchange_weak(last, newNode);
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(last, next);
                }
            }
        }
    }

    bool pop(T& result) {
        while (true) {
            Node* first = head.load();
            Node* last = tail.load();
            Node* next = first->next.load();

            if (first == head.load()) {
                if (first == last) {
                    if (next == nullptr) {
                        return false;
                    }
                    tail.compare_exchange_weak(last, next);
                } else {
                    result = next->data;

                    if (head.compare_exchange_weak(first, next)) {
                        delete first; // simplified (not safe in production)
                        return true;
                    }
                }
            }
        }
    }
};

#endif