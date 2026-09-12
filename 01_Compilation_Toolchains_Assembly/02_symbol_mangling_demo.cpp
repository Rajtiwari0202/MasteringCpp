/**
 * ============================================================================
 * MODULE 01: Compilation Pipeline & Toolchains
 * FILE: 02_symbol_mangling_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. C++ Name Mangling across Overloaded Functions & Namespaces
 * 2. `extern "C"` Linkage Block (Disabling Name Mangling)
 * 3. Inspecting symbols using objdump / nm
 * ============================================================================
 */

#include <iostream>

// 1. OVERLOADED FUNCTIONS (Will produce distinct mangled linker symbols)
void calculate(int x) {
    std::cout << "calculate(int): " << x << std::endl;
}

void calculate(double x) {
    std::cout << "calculate(double): " << x << std::endl;
}

void calculate(int x, double y) {
    std::cout << "calculate(int, double): " << x << ", " << y << std::endl;
}

// 2. NAMESPACE & CLASS METHOD (Mangled with namespace & class qualifiers)
namespace HighPerformance {
    class PhysicsEngine {
    public:
        void computeGravity(float force) {
            std::cout << "PhysicsEngine::computeGravity(float): " << force << std::endl;
        }
    };
}

// 3. EXTERN "C" BLOCK (Disables C++ name mangling for C compatibility)
extern "C" {
    void C_Compatible_Function(int code) {
        std::cout << "C_Compatible_Function(int): " << code << std::endl;
    }
}

int main() {
    calculate(10);
    calculate(3.14159);
    calculate(42, 2.718);

    HighPerformance::PhysicsEngine engine;
    engine.computeGravity(9.81f);

    C_Compatible_Function(200);

    return 0;
}
