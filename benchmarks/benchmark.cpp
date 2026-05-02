#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "LockFreeQueue.h"

LockFreeQueue<int> q;

void producer(int count) {
    for (int i = 0; i < count; i++) {
        q.push(i);
    }
}

void consumer(int count) {
    int value;
    for (int i = 0; i < count; i++) {
        while (!q.pop(value));
    }
}

int main() {
    const int ops = 100000;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(producer, ops);
    std::thread t2(consumer, ops);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Operations: " << ops << std::endl;
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    return 0;
    
}