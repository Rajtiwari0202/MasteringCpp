/**
 * ============================================================================
 * MODULE 04: OOP, Vtables & Memory Layout
 * FILE: 01_vtable_and_slicing_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Object Memory Size Difference with/without Virtual Functions (vptr injection)
 * 2. Multiple Inheritance Pointer Offset Shift (Base1* vs Base2* memory addresses)
 * 3. Object Slicing Trap vs Reference Polymorphism
 * 4. Virtual Call inside Constructor Trap
 * ============================================================================
 */

#include <iostream>

// 1. NON-VIRTUAL CLASS VS VIRTUAL CLASS
class PlainStruct {
    int x; // 4 bytes + 4 bytes padding = 8 bytes
    double y; // 8 bytes
};

class PolymorphicClass {
public:
    int x;
    double y;
    virtual void doWork() {
        std::cout << "PolymorphicClass::doWork()\n";
    }
    virtual ~PolymorphicClass() = default;
};

// 2. MULTIPLE INHERITANCE POINTER SHIFT DEMO
class Base1 {
public:
    int data1 = 100;
    virtual void func1() { std::cout << "Base1::func1()\n"; }
    virtual ~Base1() = default;
};

class Base2 {
public:
    int data2 = 200;
    virtual void func2() { std::cout << "Base2::func2()\n"; }
    virtual ~Base2() = default;
};

class Derived : public Base1, public Base2 {
public:
    int derivedData = 300;
    void func1() override { std::cout << "Derived::func1()\n"; }
    void func2() override { std::cout << "Derived::func2()\n"; }
};

// 3. OBJECT SLICING DEMO
class Parent {
public:
    int parentData = 111;
    virtual void display() const {
        std::cout << "Parent::display() - parentData: " << parentData << "\n";
    }
    virtual ~Parent() = default;
};

class Child : public Parent {
public:
    int childData = 999;
    void display() const override {
        std::cout << "Child::display() - parentData: " << parentData << ", childData: " << childData << "\n";
    }
};

void executeByValue(Parent p) { // SLICING HAPPENS HERE!
    std::cout << "[By Value] ";
    p.display();
}

void executeByReference(const Parent& p) { // POLYMORPHIC & SAFE!
    std::cout << "[By Reference] ";
    p.display();
}

// 4. VIRTUAL CALL IN CONSTRUCTOR TRAP
class BaseConstruct {
public:
    BaseConstruct() {
        std::cout << "BaseConstruct() calling virtual print()...\n";
        print(); // Will call BaseConstruct::print(), NOT DerivedConstruct::print()!
    }
    virtual void print() {
        std::cout << "--> BaseConstruct::print()\n";
    }
    virtual ~BaseConstruct() = default;
};

class DerivedConstruct : public BaseConstruct {
public:
    DerivedConstruct() {
        std::cout << "DerivedConstruct() initialized.\n";
    }
    void print() override {
        std::cout << "--> DerivedConstruct::print()\n";
    }
};

int main() {
    std::cout << "--- 1. VPTR MEMORY OVERHEAD ---" << std::endl;
    std::cout << "sizeof(PlainStruct):      " << sizeof(PlainStruct) << " bytes\n";
    std::cout << "sizeof(PolymorphicClass): " << sizeof(PolymorphicClass) << " bytes (Extra vptr injected!)\n\n";

    std::cout << "--- 2. MULTIPLE INHERITANCE POINTER SHIFT ---" << std::endl;
    Derived* d = new Derived();
    Base1* b1 = d;
    Base2* b2 = d;

    std::cout << "Derived* raw address: " << (void*)d << "\n";
    std::cout << "Base1* raw address:   " << (void*)b1 << " (Same as Derived*)\n";
    std::cout << "Base2* raw address:   " << (void*)b2 << " (Shifted by sizeof(Base1) subobject!)\n";
    std::cout << "Pointer address diff: " << ((char*)b2 - (char*)b1) << " bytes\n\n";

    std::cout << "--- 3. OBJECT SLICING DEMO ---" << std::endl;
    Child childObj;
    executeByValue(childObj);      // Sliced to Parent!
    executeByReference(childObj);  // Polymorphic execution!

    std::cout << "\n--- 4. VIRTUAL CALL IN CONSTRUCTOR TRAP ---" << std::endl;
    DerivedConstruct dc; // Inspect which print() executes during Base constructor phase!

    delete d;
    return 0;
}
