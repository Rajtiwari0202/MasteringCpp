/**
 * ============================================================================
 * MODULE 08: Templates, SFINAE & C++20 Concepts
 * FILE: 01_templates_and_concepts_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Class Template Partial & Full Specialization
 * 2. SFINAE Member Detection with std::void_t
 * 3. C++20 Concepts & Constraints (concept & requires)
 * 4. Variadic Templates & Fold Expressions (C++17)
 * 5. Custom Type Trait Implementation
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <type_traits>
#include <concepts>

// 1. CLASS TEMPLATE SPECIALIZATION
template <typename T>
struct TypeNamePrinter {
    static void print() { std::cout << "Primary Template (Generic Type)\n"; }
};

// Partial Specialization for Pointers
template <typename T>
struct TypeNamePrinter<T*> {
    static void print() { std::cout << "Partial Specialization (Pointer Type)\n"; }
};

// Full Specialization for int
template <>
struct TypeNamePrinter<int> {
    static void print() { std::cout << "Full Specialization (int)\n"; }
};

// 2. SFINAE MEMBER DETECTION (std::void_t)
template <typename T, typename = void>
struct HasSerializeMethod : std::false_type {};

template <typename T>
struct HasSerializeMethod<T, std::void_t<decltype(std::declval<T>().serialize())>> : std::true_type {};

class Order {
public:
    std::string serialize() const { return "Order_Data_JSON"; }
};

class PlainData {};

// 3. C++20 CONCEPTS & CONSTRAINTS
template <typename T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <typename T>
concept Serializable = requires(T obj) {
    { obj.serialize() } -> std::same_as<std::string>;
};

// Function constrained with C++20 Concept
template <Number T>
T multiply(T a, T b) {
    return a * b;
}

template <Serializable T>
void saveToFile(const T& obj) {
    std::cout << "Saving serialized data: " << obj.serialize() << "\n";
}

// 4. VARIADIC TEMPLATES & FOLD EXPRESSIONS (C++17)
template <typename... Args>
auto sumAll(Args... args) {
    return (... + args); // Unpacks left fold: ((arg1 + arg2) + arg3) ...
}

template <typename... Args>
void printWithSpaces(Args... args) {
    ((std::cout << args << " "), ...); // Fold over comma operator!
    std::cout << "\n";
}

int main() {
    std::cout << "--- 1. TEMPLATE SPECIALIZATION ---" << std::endl;
    TypeNamePrinter<double>::print(); // Primary
    TypeNamePrinter<char*>::print();   // Partial (pointer)
    TypeNamePrinter<int>::print();     // Full (int)

    std::cout << "\n--- 2. SFINAE MEMBER DETECTION ---" << std::endl;
    std::cout << "HasSerializeMethod<Order>:     " << std::boolalpha << HasSerializeMethod<Order>::value << "\n";
    std::cout << "HasSerializeMethod<PlainData>: " << std::boolalpha << HasSerializeMethod<PlainData>::value << "\n";

    std::cout << "\n--- 3. C++20 CONCEPTS ---" << std::endl;
    std::cout << "multiply(5, 10): " << multiply(5, 10) << "\n";
    std::cout << "multiply(2.5, 4.0): " << multiply(2.5, 4.0) << "\n";

    Order myOrder;
    saveToFile(myOrder); // Meets Serializable concept!

    std::cout << "\n--- 4. FOLD EXPRESSIONS ---" << std::endl;
    std::cout << "sumAll(1, 2, 3, 4, 5): " << sumAll(1, 2, 3, 4, 5) << "\n";
    std::cout << "sumAll(1.5, 2.5, 3.0): " << sumAll(1.5, 2.5, 3.0) << "\n";

    std::cout << "printWithSpaces output: ";
    printWithSpaces("Modern", "C++20", "Concepts", 42, 3.14159);

    return 0;
}
