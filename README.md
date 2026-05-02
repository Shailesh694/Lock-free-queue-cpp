# Lock-Free Queue (C++)

A high-performance lock-free FIFO queue implemented using atomic operations, based on the Michael–Scott algorithm.

## 🚀 Motivation

Traditional mutex-based queues suffer from contention under high concurrency.  
This project explores a lock-free design to achieve better scalability and lower latency.

---

## ⚙️ Features

- Lock-free push and pop operations
- Uses std::atomic and CAS (compare-and-swap)
- Multi-threaded producer-consumer model
- Benchmark comparison with mutex-based queue

---

## 🧠 Design Overview

- Linked-list based queue
- Dummy node to simplify edge cases
- Head and tail pointers updated atomically
- CAS ensures thread-safe updates

---

## 📊 Benchmark Results
Operations: 200000
Mutex Queue Time: 4 ms
Lock-Free Queue Time: 27 ms
Speedup: 0.14x


Lock-free design reduces contention and improves throughput.

In this workload, the mutex-based queue outperforms the lock-free implementation due to overhead from atomic operations.

This demonstrates that lock-free structures are not always faster and depend on contention and workload characteristics.

---

## 🧪 How to Run

```bash
make
./main

make compare
./compare