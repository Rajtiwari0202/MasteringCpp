/**
 * ============================================================================
 * MODULE 07: STL Deep Dive & Iterators
 * FILE: 01_stl_internals_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. std::vector Capacity Expansion, Reallocation & shrink_to_fit()
 * 2. std::unordered_map Bucket Count & Load Factor Inspection
 * 3. Custom Hash Function for User-Defined Structs
 * 4. C++20 Lazy Ranges & Views Pipelines
 * 5. Custom Range Iterator Implementation
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>
#include <string>
#include <cstddef>

// 1. CUSTOM STRUCT & HASH FUNCTION FOR UNORDERED_MAP
struct Point2D {
    int x;
    int y;

    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

// Custom Hash Specialization in std namespace
template <>
struct std::hash<Point2D> {
    size_t operator()(const Point2D& p) const noexcept {
        // Bit-combine x and y hashes
        size_t h1 = std::hash<int>{}(p.x);
        size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

// 2. CUSTOM ITERATOR CLASS DEMO (Generates numbers from start to end)
class SimpleRange {
private:
    int m_start;
    int m_end;

public:
    SimpleRange(int s, int e) : m_start(s), m_end(e) {}

    class Iterator {
    private:
        int m_current;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = int;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const int*;
        using reference         = const int&;

        Iterator(int val) : m_current(val) {}

        reference operator*() const { return m_current; }
        Iterator& operator++() { ++m_current; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        bool operator==(const Iterator& other) const { return m_current == other.m_current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    Iterator begin() const { return Iterator(m_start); }
    Iterator end() const { return Iterator(m_end); }
};

int main() {
    std::cout << "--- 1. VECTOR CAPACITY GROWTH & SHRINK_TO_FIT ---" << std::endl;
    std::vector<int> vec;
    size_t prevCapacity = vec.capacity();
    std::cout << "Initial size: " << vec.size() << " | Initial capacity: " << prevCapacity << "\n";

    for (int i = 0; i < 20; ++i) {
        vec.push_back(i);
        if (vec.capacity() != prevCapacity) {
            std::cout << "Capacity expanded from " << prevCapacity << " -> " << vec.capacity() 
                      << " (size: " << vec.size() << ")\n";
            prevCapacity = vec.capacity();
        }
    }

    vec.clear();
    std::cout << "After clear() -> size: " << vec.size() << " | capacity: " << vec.capacity() << " (Capacity retained!)\n";
    vec.shrink_to_fit();
    std::cout << "After shrink_to_fit() -> size: " << vec.size() << " | capacity: " << vec.capacity() << " (Freed!)\n\n";

    std::cout << "--- 2. UNORDERED_MAP BUCKET INSPECTION ---" << std::endl;
    std::unordered_map<Point2D, std::string> pointMap;
    std::cout << "Initial bucket_count: " << pointMap.bucket_count() << "\n";

    for (int i = 0; i < 10; ++i) {
        pointMap[{i, i * 2}] = "Point_" + std::to_string(i);
    }

    std::cout << "Size after insertions: " << pointMap.size() << "\n";
    std::cout << "Bucket count after insertions: " << pointMap.bucket_count() << "\n";
    std::cout << "Load factor: " << pointMap.load_factor() << " (Max load factor: " << pointMap.max_load_factor() << ")\n\n";

    std::cout << "--- 3. C++20 LAZY RANGES PIPELINE ---" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter even numbers and square them (Lazy evaluation!)
    auto evenSquares = numbers 
                     | std::views::filter([](int n) { return n % 2 == 0; })
                     | std::views::transform([](int n) { return n * n; });

    std::cout << "Transformed Even Squares: ";
    for (int val : evenSquares) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    std::cout << "--- 4. CUSTOM ITERATOR DEMO ---" << std::endl;
    SimpleRange range(5, 12);
    std::cout << "Custom Range values: ";
    for (int val : range) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}
