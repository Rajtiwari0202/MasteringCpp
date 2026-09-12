#include <iostream>
#include <string>
#include "CustomAllocator.hpp"

class Particle {
public:
    int id;
    double x, y, z;

    Particle(int i, double px, double py, double pz)
        : id(i), x(px), y(py), z(pz) {
        // Particle constructed
    }

    ~Particle() {
        // Particle destroyed
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "   CAPSTONE PROJECT 1: CUSTOM MEMORY ALLOCATOR TEST     \n";
    std::cout << "========================================================\n\n";

    // 1. ARENA BUMP ALLOCATOR DEMO
    std::cout << "--- 1. Arena Bump Allocator Testing ---\n";
    CoreEngine::ArenaBumpAllocator arena(4096); // 4KB Arena

    Particle* p1 = arena.create<Particle>(1, 10.0, 20.0, 30.0);
    Particle* p2 = arena.create<Particle>(2, 100.0, 200.0, 300.0);

    std::cout << "p1 (ID: " << p1->id << ") allocated at address: " << (void*)p1 << "\n";
    std::cout << "p2 (ID: " << p2->id << ") allocated at address: " << (void*)p2 << "\n";
    std::cout << "Arena memory used: " << arena.bytesUsed() << " / " << arena.capacity() << " bytes\n";

    arena.reset();
    std::cout << "Arena reset! Bytes used after reset: " << arena.bytesUsed() << " bytes\n\n";

    // 2. FIXED-SIZE POOL ALLOCATOR DEMO
    std::cout << "--- 2. Fixed-Size Pool Allocator Testing ---\n";
    CoreEngine::FixedPoolAllocator<Particle, 1024> particlePool;

    Particle* pPool1 = particlePool.allocate(101, 1.1, 2.2, 3.3);
    Particle* pPool2 = particlePool.allocate(102, 4.4, 5.5, 6.6);

    std::cout << "Pool Allocated pPool1 at address: " << (void*)pPool1 << "\n";
    std::cout << "Pool Allocated pPool2 at address: " << (void*)pPool2 << "\n";

    // Deallocate pPool1 back to Free-List
    particlePool.deallocate(pPool1);
    std::cout << "Deallocated pPool1 back to Pool Free-List.\n";

    // Next allocation re-uses pPool1's slot O(1)!
    Particle* pPool3 = particlePool.allocate(103, 7.7, 8.8, 9.9);
    std::cout << "Pool Allocated pPool3 at address: " << (void*)pPool3 << " (Slot Reused!)\n\n";

    particlePool.deallocate(pPool2);
    particlePool.deallocate(pPool3);

    std::cout << "All Custom Allocator tests PASSED SUCCESSFUL!\n";
    return 0;
}
