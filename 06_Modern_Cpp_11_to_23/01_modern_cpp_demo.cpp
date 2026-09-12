/**
 * ============================================================================
 * MODULE 06: Modern C++ Features (C++11 to C++23)
 * FILE: 01_modern_cpp_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Perfect Forwarding with std::forward
 * 2. consteval Immediate Compile-Time Computation (C++20)
 * 3. Lambda Init Captures with Move-Only Types (std::unique_ptr)
 * 4. std::variant Pattern Matching via std::visit
 * 5. std::string_view & std::span Zero-Allocation Views
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <optional>
#include <string_view>
#include <span>

// 1. PERFECT FORWARDING DEMO
void target(const std::string& lval) {
    std::cout << "target(const std::string&) -> Bound to LVALUE\n";
}

void target(std::string&& rval) {
    std::cout << "target(std::string&&) -> Bound to XVALUE/PRVALUE\n";
}

template <typename T>
void passThrough(T&& arg) {
    target(std::forward<T>(arg)); // Perfectly preserves lvalue/rvalue category!
}

// 2. CONSTEVAL IMMEDIATE FUNCTION (C++20)
consteval uint64_t compileTimeFactorial(uint32_t n) {
    uint64_t result = 1;
    for (uint32_t i = 1; i <= n; ++i) result *= i;
    return result;
}

// 3. ZERO-COPY VIEWS (std::string_view & std::span)
void printSubString(std::string_view sv) {
    std::cout << "string_view (Length: " << sv.length() << "): " << sv << "\n";
}

void printSlice(std::span<const int> s) {
    std::cout << "span slice elements: ";
    for (int elem : s) std::cout << elem << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "--- 1. PERFECT FORWARDING ---" << std::endl;
    std::string str = "Persistent Lvalue String";
    passThrough(str);                 // Passes Lvalue
    passThrough(std::move(str));      // Passes Xvalue
    passThrough("PRvalue Literal");   // Passes PRvalue

    std::cout << "\n--- 2. CONSTEVAL COMPILE-TIME COMPUTATION ---" << std::endl;
    constexpr uint64_t fact10 = compileTimeFactorial(10); // Computed at compile time!
    std::cout << "10! (Factorial computed by compiler at build-time): " << fact10 << "\n";

    std::cout << "\n--- 3. LAMBDA MOVE-ONLY CAPTURE ---" << std::endl;
    auto uniqueRes = std::make_unique<int>(999);
    
    // Move unique_ptr into lambda closure using C++14 init capture!
    auto lambda = [res = std::move(uniqueRes)]() {
        std::cout << "Inside lambda, captured unique_ptr value: " << *res << "\n";
    };
    lambda();
    std::cout << "Outside lambda, uniqueRes is now nullptr: " << (uniqueRes == nullptr ? "true" : "false") << "\n";

    std::cout << "\n--- 4. STD::VARIANT & STD::VISIT ---" << std::endl;
    std::variant<int, double, std::string> var = 3.14159;

    std::visit([](auto&& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, int>)
            std::cout << "Variant holds int: " << val << "\n";
        else if constexpr (std::is_same_v<T, double>)
            std::cout << "Variant holds double: " << val << "\n";
        else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "Variant holds string: " << val << "\n";
    }, var);

    std::cout << "\n--- 5. ZERO-ALLOCATION VIEWS (STRING_VIEW & SPAN) ---" << std::endl;
    std::string fullText = "High Performance C++20 Systems Programming";
    printSubString(std::string_view(fullText).substr(5, 11)); // Zero heap allocation!

    std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80};
    printSlice(std::span<const int>(numbers).subspan(2, 4)); // Subspan view over vector!

    return 0;
}
