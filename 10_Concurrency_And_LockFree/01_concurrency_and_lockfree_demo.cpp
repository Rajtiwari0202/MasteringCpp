/**
 * ============================================================================
 * MODULE 10: Concurrency & Lock-Free Programming
 * FILE: 01_concurrency_and_lockfree_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Deadlock-Free Multi-Mutex Locking with std::scoped_lock
 * 2. Producer-Consumer Synchronization using Atomic Acquire-Release Semantics
 * 3. Lock-Free Single-Producer Single-Consumer (SPSC) Ring Buffer
 * ============================================================================
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <array>
#include <chrono>

// 1. DEADLOCK-FREE MULTI-MUTEX LOCKING (std::scoped_lock)
struct Account {
    std::mutex mtx;
    int balance;
    Account(int b) : balance(b) {}
};

void transferMoney(Account& from, Account& to, int amount) {
    // std::scoped_lock uses deadlock-avoidance algorithm (lock std::lock under the hood)
    std::scoped_lock lock(from.mtx, to.mtx);
    from.balance -= amount;
    to.balance += amount;
    std::cout << "Transferred $" << amount << " | From: $" << from.balance << " | To: $" << to.balance << "\n";
}

// 2. LOCK-FREE SPSC RING BUFFER CLASS
template <typename T, size_t Capacity>
class LockFreeSPSCQueue {
private:
    static_assert((Capacity & (Capacity - 1)) == 0, "Capacity must be a power of 2!");
    
    std::array<T, Capacity> m_buffer;
    
    // Align head and tail to 64-byte boundaries to prevent False Sharing!
    alignas(64) std::atomic<size_t> m_head{0}; // Written by Producer
    alignas(64) std::atomic<size_t> m_tail{0}; // Written by Consumer

public:
    LockFreeSPSCQueue() = default;

    bool push(const T& item) {
        size_t currentHead = m_head.load(std::memory_order_relaxed);
        size_t currentTail = m_tail.load(std::memory_order_acquire);

        if ((currentHead - currentTail) == Capacity) {
            return false; // Queue is full!
        }

        m_buffer[currentHead & (Capacity - 1)] = item;
        
        // Release store guarantees buffer write is visible BEFORE head increment!
        m_head.store(currentHead + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t currentTail = m_tail.load(std::memory_order_relaxed);
        size_t currentHead = m_head.load(std::memory_order_acquire);

        if (currentTail == currentHead) {
            return false; // Queue is empty!
        }

        item = m_buffer[currentTail & (Capacity - 1)];
        
        // Release store guarantees item read is finished BEFORE tail increment!
        m_tail.store(currentTail + 1, std::memory_order_release);
        return true;
    }

    size_t size() const {
        return m_head.load(std::memory_order_relaxed) - m_tail.load(std::memory_order_relaxed);
    }
};

int main() {
    std::cout << "--- 1. DEADLOCK-FREE SCOPED_LOCK DEMO ---" << std::endl;
    Account acc1(1000);
    Account acc2(500);

    std::thread t1([&]() { transferMoney(acc1, acc2, 200); });
    std::thread t2([&]() { transferMoney(acc2, acc1, 100); });
    t1.join();
    t2.join();
    std::cout << "\n";

    std::cout << "--- 2. LOCK-FREE SPSC RING BUFFER DEMO ---" << std::endl;
    LockFreeSPSCQueue<int, 1024> spscQueue;
    const int NUM_ELEMENTS = 100'000;
    
    std::atomic<bool> producerDone{false};
    uint64_t consumedSum = 0;

    // Producer Thread
    std::thread producer([&]() {
        for (int i = 1; i <= NUM_ELEMENTS; ++i) {
            while (!spscQueue.push(i)) {
                std::this_thread::yield(); // Spin until space available
            }
        }
        producerDone.store(true, std::memory_order_release);
    });

    // Consumer Thread
    std::thread consumer([&]() {
        int item = 0;
        while (!producerDone.load(std::memory_order_acquire) || spscQueue.size() > 0) {
            if (spscQueue.pop(item)) {
                consumedSum += item;
            } else {
                std::this_thread::yield();
            }
        }
    });

    producer.join();
    consumer.join();

    uint64_t expectedSum = (uint64_t)NUM_ELEMENTS * (NUM_ELEMENTS + 1) / 2;
    std::cout << "Pushed " << NUM_ELEMENTS << " elements through Lock-Free Ring Buffer!\n";
    std::cout << "Consumed Sum: " << consumedSum << " (Expected: " << expectedSum << ")\n";
    std::cout << "Lock-Free SPSC Test: " << (consumedSum == expectedSum ? "PASSED SUCCESSFUL!" : "FAILED!") << "\n";

    return 0;
}
