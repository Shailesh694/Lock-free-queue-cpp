#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>
#include "LockFreeQueue.h"

using namespace std;

/* =========================
   Mutex Queue
========================= */
template<typename T>
class MutexQueue {
private:
    queue<T> q;
    mutex m;

public:
    void push(T val) {
        lock_guard<mutex> lock(m);
        q.push(val);
    }

    bool pop(T &val) {
        lock_guard<mutex> lock(m);
        if (q.empty()) return false;
        val = q.front();
        q.pop();
        return true;
    }
};

/* =========================
   Benchmark Function
========================= */
template<typename QueueType>
long long runBenchmark(QueueType& q, int ops) {
    auto start = chrono::high_resolution_clock::now();

    thread producer([&]() {
        for (int i = 0; i < ops; i++) {
            q.push(i);
        }
    });

    thread consumer([&]() {
        int value;
        for (int i = 0; i < ops; i++) {
            while (!q.pop(value));
        }
    });

    producer.join();
    consumer.join();

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

/* =========================
   MAIN
========================= */
int main() {
    const int ops = 200000;

    // Mutex queue
    MutexQueue<int> mq;
    long long mutexTime = runBenchmark(mq, ops);

    // Lock-free queue
    LockFreeQueue<int> lfq;
    long long lockfreeTime = runBenchmark(lfq, ops);

    cout << "Operations: " << ops << endl;
    cout << "Mutex Queue Time: " << mutexTime << " ms" << endl;
    cout << "Lock-Free Queue Time: " << lockfreeTime << " ms" << endl;

    double speedup = (double)mutexTime / lockfreeTime;
    cout << "Speedup: " << speedup << "x" << endl;

    return 0;
}