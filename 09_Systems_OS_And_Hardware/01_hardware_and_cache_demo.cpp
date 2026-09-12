/**
 * ============================================================================
 * MODULE 09: Systems OS & Hardware Mechanics
 * FILE: 01_hardware_and_cache_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. CPU Cache Miss Benchmark: Sequential Array Traversal vs Random Pointer Chasing
 * 2. False Sharing Benchmark: Unaligned Shared Counters vs Cache-Line Isolated (alignas 64)
 * 3. Array-of-Structures (AoS) vs Structure-of-Arrays (SoA) Cache Locality
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>
#include <atomic>
#include <random>
#include <algorithm>

// Timer Utility for Microbenchmarking
class ScopedTimer {
private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_start;

public:
    ScopedTimer(std::string name) 
        : m_name(name), m_start(std::chrono::high_resolution_clock::now()) {}

    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count();
        std::cout << "[" << m_name << "] Time Elapsed: " << duration << " us (" << (duration / 1000.0) << " ms)\n";
    }
};

// 1. POINTER CHASING NODE STRUCT
struct Node {
    int data;
    Node* next;
};

// 2. FALSE SHARING STRUCTS
struct UnalignedCounters {
    std::atomic<uint64_t> counter1{0}; // Both counters share the SAME 64-byte cache line!
    std::atomic<uint64_t> counter2{0};
};

struct AlignedCounters {
    alignas(64) std::atomic<uint64_t> counter1{0}; // Isolated on Cache Line 1
    alignas(64) std::atomic<uint64_t> counter2{0}; // Isolated on Cache Line 2
};

const int ITERATIONS = 20'000'000;

void benchmarkCacheMisses() {
    std::cout << "--- 1. CACHE MISS BENCHMARK: ARRAY VS POINTER CHASING ---" << std::endl;
    const size_t N = 5'000'000;
    
    // Contiguous Array Allocation
    std::vector<int> array(N, 1);
    
    // Linked Nodes Allocation (Pointer Chasing)
    std::vector<Node> nodes(N);
    for (size_t i = 0; i < N - 1; ++i) {
        nodes[i].data = 1;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[N - 1].data = 1;
    nodes[N - 1].next = nullptr;

    // Shuffle node pointers to simulate fragmented heap pointer chasing!
    std::vector<size_t> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::mt19937 rng(42);
    std::shuffle(indices.begin(), indices.end(), rng);

    for (size_t i = 0; i < N - 1; ++i) {
        nodes[indices[i]].next = &nodes[indices[i + 1]];
    }
    nodes[indices[N - 1]].next = nullptr;

    // Benchmark 1: Contiguous Vector Sum (100% L1 Cache Hits)
    volatile uint64_t sumArray = 0;
    {
        ScopedTimer timer("1. Contiguous Vector Traversal (Cache-Friendly)");
        for (size_t i = 0; i < N; ++i) {
            sumArray += array[i];
        }
    }

    // Benchmark 2: Fragmented Pointer Chasing Traversal (L1 Cache Miss Stalls)
    volatile uint64_t sumList = 0;
    {
        ScopedTimer timer("2. Fragmented Pointer Chasing (Cache-Unfriendly)");
        Node* curr = &nodes[indices[0]];
        while (curr) {
            sumList += curr->data;
            curr = curr->next;
        }
    }
    std::cout << "\n";
}

void benchmarkFalseSharing() {
    std::cout << "--- 2. FALSE SHARING MULTI-THREADED BENCHMARK ---" << std::endl;
    
    // Unaligned Benchmark
    {
        UnalignedCounters unaligned;
        ScopedTimer timer("False Sharing (Unaligned Counters)");
        std::thread t1([&]() {
            for (int i = 0; i < ITERATIONS; ++i) unaligned.counter1.fetch_add(1, std::memory_order_relaxed);
        });
        std::thread t2([&]() {
            for (int i = 0; i < ITERATIONS; ++i) unaligned.counter2.fetch_add(1, std::memory_order_relaxed);
        });
        t1.join();
        t2.join();
    }

    // Aligned Benchmark (Cache-Line Isolated)
    {
        AlignedCounters aligned;
        ScopedTimer timer("Isolated Cache-Lines (alignas 64)");
        std::thread t1([&]() {
            for (int i = 0; i < ITERATIONS; ++i) aligned.counter1.fetch_add(1, std::memory_order_relaxed);
        });
        std::thread t2([&]() {
            for (int i = 0; i < ITERATIONS; ++i) aligned.counter2.fetch_add(1, std::memory_order_relaxed);
        });
        t1.join();
        t2.join();
    }
    std::cout << "\n";
}

int main() {
    benchmarkCacheMisses();
    benchmarkFalseSharing();
    return 0;
}
