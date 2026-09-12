/**
 * ============================================================================
 * MODULE 02: Memory Layout & Primitives
 * FILE: 01_alignment_and_padding_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Measuring Virtual Memory Address Ranges (Stack vs Heap vs Data vs BSS)
 * 2. Struct Padding, Member Alignment & Offset Inspection (offsetof)
 * 3. alignof & alignas Custom Cache-Line Alignment (64-byte)
 * 4. Floating Point Bit-Level Inspection (Sign, Exponent, Mantissa via std::bit_cast)
 * 5. Unsigned Wrapping vs Signed Overflow Safety
 * ============================================================================
 */

#include <iostream>
#include <cstddef>     // offsetof
#include <cstdint>     // uint32_t, uint64_t
#include <bit>         // std::bit_cast (C++20)
#include <bitset>      // std::bitset

// Globals to inspect Data and BSS memory addresses
int g_initialized_var = 42; // Data segment
int g_uninitialized_var;    // BSS segment

// 1. STRUCT PADDING DEMONSTRATION
struct BadLayout {
    char a;      // 1 byte
    // 3 bytes padding
    int b;       // 4 bytes
    char c;      // 1 byte
    // 7 bytes padding
    double d;    // 8 bytes
}; // Total: 24 bytes!

struct GoodLayout {
    double d;    // 8 bytes
    int b;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // 2 bytes padding
}; // Total: 16 bytes!

// Cache-Line Aligned Struct (64-byte boundary to prevent false sharing)
struct alignas(64) CacheLineIsolatedCounter {
    uint64_t value;
};

// Helper function to print bit pattern of float
void inspect_float_bits(float f) {
    uint32_t bits = std::bit_cast<uint32_t>(f);
    std::bitset<32> b(bits);
    std::cout << "Float value: " << f << " | Binary: " 
              << b.to_string().substr(0, 1) << " "      // Sign bit
              << b.to_string().substr(1, 8) << " "      // Exponent (8 bits)
              << b.to_string().substr(9, 23) << "\n";   // Mantissa (23 bits)
}

int main() {
    std::cout << "--- 1. VIRTUAL MEMORY ADDRESS SPACES ---" << std::endl;
    int stack_var = 10;
    int* heap_var = new int(20);

    std::cout << "Text Segment (Function code): " << (void*)&main << std::endl;
    std::cout << "Data Segment (g_initialized_var): " << (void*)&g_initialized_var << std::endl;
    std::cout << "BSS Segment  (g_uninitialized_var): " << (void*)&g_uninitialized_var << std::endl;
    std::cout << "Heap Segment (heap_var address): " << (void*)heap_var << std::endl;
    std::cout << "Stack Segment (stack_var address): " << (void*)&stack_var << std::endl << std::endl;

    std::cout << "--- 2. STRUCT PADDING & OFFSETOF ---" << std::endl;
    std::cout << "sizeof(BadLayout):  " << sizeof(BadLayout) << " bytes (Padding inflated size!)\n";
    std::cout << "  - offsetof(a): " << offsetof(BadLayout, a) << "\n";
    std::cout << "  - offsetof(b): " << offsetof(BadLayout, b) << "\n";
    std::cout << "  - offsetof(c): " << offsetof(BadLayout, c) << "\n";
    std::cout << "  - offsetof(d): " << offsetof(BadLayout, d) << "\n";

    std::cout << "\nsizeof(GoodLayout): " << sizeof(GoodLayout) << " bytes (Optimal arrangement!)\n";
    std::cout << "  - offsetof(d): " << offsetof(GoodLayout, d) << "\n";
    std::cout << "  - offsetof(b): " << offsetof(GoodLayout, b) << "\n";
    std::cout << "  - offsetof(a): " << offsetof(GoodLayout, a) << "\n";
    std::cout << "  - offsetof(c): " << offsetof(GoodLayout, c) << "\n\n";

    std::cout << "--- 3. ALIGNOF & ALIGNAS ---" << std::endl;
    std::cout << "alignof(BadLayout): " << alignof(BadLayout) << "\n";
    std::cout << "alignof(CacheLineIsolatedCounter): " << alignof(CacheLineIsolatedCounter) << "\n";
    std::cout << "sizeof(CacheLineIsolatedCounter): " << sizeof(CacheLineIsolatedCounter) << " bytes\n\n";

    std::cout << "--- 4. IEEE 754 FLOAT BIT INSPECTION ---" << std::endl;
    inspect_float_bits(1.0f);
    inspect_float_bits(-1.0f);
    inspect_float_bits(0.1f);
    inspect_float_bits(0.0f);

    std::cout << "\n--- 5. UNSIGNED WRAPPING MECHANICS ---" << std::endl;
    uint32_t max_u = 4294967295u; // UINT32_MAX
    std::cout << "UINT32_MAX: " << max_u << std::endl;
    std::cout << "UINT32_MAX + 1 (Guaranteed Modulo Wrapping): " << (max_u + 1) << std::endl;
    uint32_t zero_u = 0u;
    std::cout << "0u - 1u (Unsigned Underflow Wrapping): " << (zero_u - 1u) << std::endl;

    delete heap_var;
    return 0;
}
