/**
 * ============================================================================
 * MODULE 05: Smart Pointers & Custom Allocators
 * FILE: 01_smart_pointers_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Placement new and Explicit Destructor Invocation
 * 2. std::unique_ptr with Custom Deleter
 * 3. std::shared_ptr Reference Counting Mechanics
 * 4. Breaking Circular References with std::weak_ptr
 * 5. Simple Arena Bump Allocator Implementation
 * ============================================================================
 */

#include <iostream>
#include <memory>
#include <vector>
#include <cstddef>
#include <cstdint>

// 1. PLACEMENT NEW DEMO CLASS
class Widget {
public:
    int id;
    Widget(int i) : id(i) {
        std::cout << "Widget(" << id << ") constructed at " << (void*)this << "\n";
    }
    ~Widget() {
        std::cout << "~Widget(" << id << ") destroyed at " << (void*)this << "\n";
    }
};

// 2. CIRCULAR REFERENCE DEMO CLASSES
struct NodeWeak; // Forward declaration

struct NodeShared {
    std::string name;
    std::shared_ptr<NodeShared> next; // Strong reference (Can cause circular leak!)
    NodeShared(std::string n) : name(n) { std::cout << "NodeShared(" << name << ") created\n"; }
    ~NodeShared() { std::cout << "~NodeShared(" << name << ") DESTROYED\n"; }
};

struct NodeWeak {
    std::string name;
    std::weak_ptr<NodeWeak> next; // Weak reference (Breaks circular leak!)
    NodeWeak(std::string n) : name(n) { std::cout << "NodeWeak(" << name << ") created\n"; }
    ~NodeWeak() { std::cout << "~NodeWeak(" << name << ") DESTROYED\n"; }
};

// 3. SIMPLE ARENA BUMP ALLOCATOR
class ArenaAllocator {
private:
    std::vector<char> m_buffer;
    size_t m_offset = 0;

public:
    ArenaAllocator(size_t bytes) : m_buffer(bytes) {}

    void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t)) {
        // Calculate aligned address offset
        uintptr_t currentAddress = reinterpret_cast<uintptr_t>(m_buffer.data() + m_offset);
        size_t padding = (alignment - (currentAddress % alignment)) % alignment;

        if (m_offset + padding + bytes > m_buffer.size()) {
            throw std::bad_alloc(); // Arena out of memory!
        }

        m_offset += padding;
        void* ptr = m_buffer.data() + m_offset;
        m_offset += bytes;
        return ptr;
    }

    void reset() {
        m_offset = 0; // O(1) instantaneous memory clear!
    }

    size_t bytesUsed() const { return m_offset; }
};

int main() {
    std::cout << "--- 1. PLACEMENT NEW & EXPLICIT DESTRUCTOR ---" << std::endl;
    alignas(Widget) char rawBuffer[sizeof(Widget)];
    
    // Construct inside rawBuffer
    Widget* wPtr = new (rawBuffer) Widget(42);
    
    // Explicit destructor invocation required!
    wPtr->~Widget();

    std::cout << "\n--- 2. UNIQUE_PTR WITH CUSTOM DELETER ---" << std::endl;
    {
        auto customDeleter = [](Widget* p) {
            std::cout << "[Custom Deleter] Deleting Widget at " << (void*)p << "\n";
            delete p;
        };
        std::unique_ptr<Widget, decltype(customDeleter)> uniqueWidget(new Widget(99), customDeleter);
    } // Custom deleter invoked cleanly here

    std::cout << "\n--- 3. SHARED_PTR & WEAK_PTR CIRCULAR REF SOLVER ---" << std::endl;
    std::cout << "Creating CIRCULAR WEAK_PTR Graph (Proper destruction):\n";
    {
        auto nodeA = std::make_shared<NodeWeak>("A");
        auto nodeB = std::make_shared<NodeWeak>("B");

        nodeA->next = nodeB; // A points to B (weak)
        nodeB->next = nodeA; // B points to A (weak)

        std::cout << "nodeA use_count: " << nodeA.use_count() << "\n";
        std::cout << "nodeB use_count: " << nodeB.use_count() << "\n";
    } // Both nodes destroyed cleanly!

    std::cout << "\n--- 4. ARENA BUMP ALLOCATOR DEMO ---" << std::endl;
    ArenaAllocator arena(1024); // 1KB Arena
    
    void* mem1 = arena.allocate(sizeof(int), alignof(int));
    int* val1 = new (mem1) int(12345);
    
    void* mem2 = arena.allocate(sizeof(double), alignof(double));
    double* val2 = new (mem2) double(99.99);

    std::cout << "Arena allocated val1: " << *val1 << " at " << mem1 << "\n";
    std::cout << "Arena allocated val2: " << *val2 << " at " << mem2 << "\n";
    std::cout << "Arena total bytes used: " << arena.bytesUsed() << " bytes\n";
    
    arena.reset(); // Instant O(1) bulk deallocation!
    std::cout << "Arena reset. Bytes used after reset: " << arena.bytesUsed() << " bytes\n";

    return 0;
}
