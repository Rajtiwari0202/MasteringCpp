/**
 * ============================================================================
 * MODULE 03: Pointers, References & Value Categories
 * FILE: 01_value_categories_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Pointer Arithmetic Scaling by sizeof(T)
 * 2. Const Reference Temporary Lifetime Extension
 * 3. Value Category Expression Taxonomy (Lvalue, PRvalue, Xvalue)
 * 4. Named Rvalue References are Lvalues Trap!
 * 5. Pointers to Member Variables and Functions (T::*)
 * 6. Reference Collapsing Demonstration
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// Helper to inspect Value Category at Compile-Time
template <typename T>
void print_value_category(T&& param) {
    if constexpr (std::is_lvalue_reference_v<T&&>) {
        std::cout << "Expression is an LVALUE\n";
    } else if constexpr (std::is_rvalue_reference_v<T&&>) {
        std::cout << "Expression is an RVALUE (PRvalue or Xvalue)\n";
    }
}

// Function returning by value (returns PRvalue)
std::string createTemporaryString() {
    return "Temporary String Content";
}

// Function returning by reference (returns Lvalue)
std::string& getGlobalString() {
    static std::string g_str = "Global Persistent String";
    return g_str;
}

class Hero {
public:
    int health = 100;
    void attack() const {
        std::cout << "Hero attacks with health: " << health << "\n";
    }
};

int main() {
    std::cout << "--- 1. POINTER ARITHMETIC SCALING ---" << std::endl;
    int arr[3] = {10, 20, 30};
    int* p = arr;
    std::cout << "p (arr[0] address): " << (void*)p << " | Value: " << *p << "\n";
    p = p + 1; // Scaled by sizeof(int) = 4 bytes
    std::cout << "p + 1 (arr[1] address): " << (void*)p << " | Value: " << *p << "\n\n";

    std::cout << "--- 2. CONST REF LIFETIME EXTENSION ---" << std::endl;
    {
        const std::string& ref = createTemporaryString(); // Extended lifetime!
        std::cout << "Ref bound to PRvalue string: " << ref << "\n";
    } // Temporary destroyed here cleanly

    std::cout << "\n--- 3. VALUE CATEGORY TAXONOMY ---" << std::endl;
    int x = 42;
    std::cout << "Variable 'x': ";
    print_value_category(x);                  // Lvalue

    std::cout << "Literal '42': ";
    print_value_category(42);                 // PRvalue

    std::cout << "Expression 'x + 5': ";
    print_value_category(x + 5);              // PRvalue

    std::cout << "std::move(x): ";
    print_value_category(std::move(x));       // Xvalue

    std::cout << "getGlobalString(): ";
    print_value_category(getGlobalString());  // Lvalue

    std::cout << "\n--- 4. NAMED RVALUE REF IS AN LVALUE TRAP ---" << std::endl;
    int&& rref = 100; // rref is an Rvalue Reference variable...
    std::cout << "Variable 'rref' itself is an: ";
    print_value_category(rref); // ...BUT the variable expression 'rref' is an LVALUE!
    std::cout << "std::move(rref) expression is an: ";
    print_value_category(std::move(rref)); // Stolen as Xvalue!

    std::cout << "\n--- 5. POINTERS TO MEMBERS (T::*) ---" << std::endl;
    int Hero::* healthPtr = &Hero::health;
    void (Hero::* attackPtr)() const = &Hero::attack;

    Hero heroInstance;
    heroInstance.*healthPtr = 250;
    (heroInstance.*attackPtr)();

    Hero* heroPointer = &heroInstance;
    heroPointer->*healthPtr = 500;
    (heroPointer->*attackPtr)();

    return 0;
}
