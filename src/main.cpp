#include <iostream>
#include <thread>
#include "LockFreeQueue.h"

LockFreeQueue<int> q;

void producer() {
    for (int i = 0; i < 1000; i++) {
        q.push(i);
    }
}

void consumer() {
    int value;
    for (int i = 0; i < 1000; i++) {
        while (!q.pop(value));
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    std::cout << "Queue test completed\n";
    return 0;
}