/**
 * ============================================================================
 * MODULE 12: Interview Traps & Misconceptions
 * FILE: 01_interview_traps_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Safe Bit Aliasing with std::bit_cast (Avoiding Strict Aliasing UB)
 * 2. Vector Iterator Invalidation Prevention
 * 3. Copy-and-Swap Idiom for Strong Exception Safety Guarantee
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <bit>
#include <cstdint>
#include <algorithm>
#include <utility>

// 1. COPY-AND-SWAP IDIOM FOR STRONG EXCEPTION SAFETY
class ExceptionSafeBuffer {
private:
    size_t m_size;
    int* m_data;

public:
    ExceptionSafeBuffer(size_t size) 
        : m_size(size), m_data(size > 0 ? new int[size]() : nullptr) {
        std::cout << "ExceptionSafeBuffer(" << m_size << ") constructed\n";
    }

    ~ExceptionSafeBuffer() {
        delete[] m_data;
        std::cout << "~ExceptionSafeBuffer(" << m_size << ") destroyed\n";
    }

    // Copy Constructor
    ExceptionSafeBuffer(const ExceptionSafeBuffer& other) 
        : m_size(other.m_size), m_data(other.m_size > 0 ? new int[other.m_size] : nullptr) {
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }

    // Move Constructor
    ExceptionSafeBuffer(ExceptionSafeBuffer&& other) noexcept 
        : m_size(0), m_data(nullptr) {
        swap(*this, other);
    }

    // Friend Swap Function (Nothrow guarantee)
    friend void swap(ExceptionSafeBuffer& first, ExceptionSafeBuffer& second) noexcept {
        using std::swap;
        swap(first.m_size, second.m_size);
        swap(first.m_data, second.m_data);
    }

    // COPY-AND-SWAP ASSIGNMENT OPERATOR (Strong Exception Guarantee!)
    // 'other' is passed BY VALUE (Copy created automatically). If copy throws, original object is untouched!
    ExceptionSafeBuffer& operator=(ExceptionSafeBuffer other) noexcept {
        swap(*this, other);
        return *this;
    }

    size_t size() const { return m_size; }
};

int main() {
    std::cout << "--- 1. SAFE BIT ALIASING (std::bit_cast vs UB) ---" << std::endl;
    float f = 3.14159f;
    
    // BAD (Strict Aliasing UB): uint32_t u = *(uint32_t*)&f;
    // GOOD (C++20 Type-Safe & UB-Free Bit Cast):
    uint32_t u = std::bit_cast<uint32_t>(f);
    std::cout << "Float: " << f << " | Safe bit_cast integer value: " << u << "\n\n";

    std::cout << "--- 2. SAFE VECTOR ITERATOR MODIFICATION ---" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    
    // Erase even numbers safely during iteration using iterator return value!
    for (auto it = numbers.begin(); it != numbers.end(); /* no increment */) {
        if (*it % 2 == 0) {
            it = numbers.erase(it); // erase returns valid iterator to next element!
        } else {
            ++it;
        }
    }

    std::cout << "Vector elements after safe erase: ";
    for (int val : numbers) std::cout << val << " ";
    std::cout << "\n\n";

    std::cout << "--- 3. COPY-AND-SWAP STRONG EXCEPTION SAFETY ---" << std::endl;
    ExceptionSafeBuffer buf1(100);
    ExceptionSafeBuffer buf2(500);

    std::cout << "Assigning buf2 to buf1 via Copy-and-Swap...\n";
    buf1 = buf2; // Strong Exception Guarantee transaction!
    std::cout << "buf1 new size: " << buf1.size() << "\n";

    return 0;
}
