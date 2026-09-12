/**
 * ============================================================================
 * MODULE 01: Compilation Pipeline & Toolchains
 * FILE: 01_preprocessing_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Macro Expansion & Preprocessor Text Substitutions
 * 2. Preprocessor Traps (Parentheses Evaluation Mistakes)
 * 3. Token Stringification Operator (#) & Token Concatenation Operator (##)
 * 4. Conditional Compilation (#ifdef, #if, #else, #endif)
 * 5. Predefined Compiler Macros (__FILE__, __LINE__, __DATE__, __cplusplus)
 * ============================================================================
 */

#include <iostream>

// 1. MACRO DEFINITIONS & TRAPS
// Bad macro: missing parentheses leads to operator precedence bugs!
#define BAD_SQUARE(x) x * x

// Good macro: fully parenthesized
#define GOOD_SQUARE(x) ((x) * (x))

// Modern C++ Alternative: constexpr inline function (Type-safe & Zero Preprocessor Trap)
template <typename T>
constexpr T inline_square(T x) {
    return x * x;
}

// 2. STRINGIFICATION (#) AND TOKEN CONCATENATION (##)
// #x turns variable name into a string literal
#define PRINT_EXPR(expr) std::cout << #expr << " = " << (expr) << std::endl

// ## concatenates two tokens into a single identifier at preprocess time
#define DECLARE_VAR(type, name) type var_##name = 100

// 3. CONDITIONAL COMPILATION
#define DEBUG_MODE 1

int main() {
    std::cout << "--- 1. MACRO TRAP DEMO ---" << std::endl;
    int a = 3 + 1; // 4
    
    // BAD_SQUARE(3 + 1) expands to: 3 + 1 * 3 + 1 = 3 + 3 + 1 = 7 (WRONG!)
    std::cout << "BAD_SQUARE(3 + 1) = " << BAD_SQUARE(a) << " (Expected 16, got wrong result if passed expression directly!)\n";
    std::cout << "BAD_SQUARE(3 + 1) direct: " << BAD_SQUARE(3 + 1) << " (Evaluates 3 + 1 * 3 + 1 = 7)\n";
    std::cout << "GOOD_SQUARE(3 + 1) direct: " << GOOD_SQUARE(3 + 1) << " (Evaluates ((3 + 1) * (3 + 1)) = 16)\n";
    std::cout << "constexpr inline_square(3 + 1): " << inline_square(3 + 1) << " (Type-safe & evaluated cleanly)\n\n";

    std::cout << "--- 2. STRINGIFICATION & CONCATENATION ---" << std::endl;
    int value = 42;
    PRINT_EXPR(value * 2 + 5);

    DECLARE_VAR(int, counter); // Expands to: int var_counter = 100;
    std::cout << "Concatenated variable var_counter = " << var_counter << std::endl << std::endl;

    std::cout << "--- 3. PREDEFINED COMPILER METADATA ---" << std::endl;
    std::cout << "Source File: " << __FILE__ << std::endl;
    std::cout << "Current Line: " << __LINE__ << std::endl;
    std::cout << "Compiled Date: " << __DATE__ << std::endl;
    std::cout << "C++ Standard Version Macro (__cplusplus): " << __cplusplus << std::endl << std::endl;

    std::cout << "--- 4. CONDITIONAL COMPILATION ---" << std::endl;
#if defined(DEBUG_MODE) && DEBUG_MODE == 1
    std::cout << "[DEBUG] Debug mode is ENABLED." << std::endl;
#else
    std::cout << "[RELEASE] Release mode active." << std::endl;
#endif

    return 0;
}
