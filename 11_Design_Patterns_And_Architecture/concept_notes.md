# 🔬 Tier 10: Advanced Design Patterns & Modern C++ Architecture

> **Architect's Perspective**: Idiomatic C++ design patterns leverage compile-time type resolution (CRTP, Policy Design) and strict RAII encasing to achieve clean modularity with **zero runtime abstraction penalties**.

---

## 1. Meyers Singleton (Thread-Safe Static Initialization)

In C++11 and beyond, local `static` variable initialization is guaranteed by the C++ standard to be **thread-safe** (Meyers Singleton).

```cpp
class DatabaseConnectionManager {
private:
    DatabaseConnectionManager() { /* Establish connection pool */ }
    ~DatabaseConnectionManager() = default;

public:
    DatabaseConnectionManager(const DatabaseConnectionManager&) = delete;
    DatabaseConnectionManager& operator=(const DatabaseConnectionManager&) = delete;

    static DatabaseConnectionManager& getInstance() {
        // Guaranteed thread-safe lazy initialization on first call!
        static DatabaseConnectionManager instance;
        return instance;
    }
};
```

---

## 2. The Pimpl Idiom (Pointer to Implementation)

The **Pimpl Idiom** (Compilation Firewall) moves a class's private data members and internal header inclusions out of the public header into a forward-declared implementation class in the `.cpp` file.

### Header File (`Widget.h`):
```cpp
#pragma once
#include <memory>

class Widget {
public:
    Widget();
    ~Widget(); // MUST be declared in header, defined in .cpp where Implementation size is known!
    
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;

    void doWork();

private:
    class Implementation; // Forward declaration
    std::unique_ptr<Implementation> m_pimpl; // Opaque implementation pointer!
};
```

### Advantages of Pimpl:
1. **Compilation Firewall**: Changing private data members in `Widget::Implementation` does NOT force re-compilation of external files that `#include "Widget.h"`!
2. **Fast Build Times**: Reduces header include dependencies in large production codebases.
3. **ABI Stability**: Binary layout of `Widget` class remains constant across version updates.

---

## 3. CRTP (Curiously Recurring Template Pattern) — Static Polymorphism

CRTP achieves polymorphic behavior at **compile-time**, eliminating `vptr`/`vtable` overhead entirely!

```cpp
// Base Template Class
template <typename Derived>
class BaseControl {
public:
    void process() {
        // Cast 'this' to Derived type at compile time!
        static_cast<Derived*>(this)->processImpl();
    }
};

// Derived Class passing ITSELF as the template parameter
class CustomButton : public BaseControl<CustomButton> {
public:
    void processImpl() {
        std::cout << "CustomButton processing event (Inlined at assembly level!)\n";
    }
};
```

### Comparison: Virtual Polymorphism vs CRTP Static Polymorphism

| Metric | Virtual Polymorphism (`virtual`) | CRTP Static Polymorphism |
| :--- | :--- | :--- |
| **Dispatch Timing** | Runtime (via `vptr` lookup) | **Compile-Time** (via Direct Call) |
| **Inlining Support** | Rare (Requires Devirtualization) | **Fully Inlined** by Compiler |
| **Memory Overhead** | 8 bytes `vptr` per object instance | **0 bytes overhead** |
| **Heterogeneous Containers** | Supported (`std::vector<Base*>`) | Not supported (Types are distinct) |

---

## 4. Policy-Based Design

Policy-based design decomposes a class into orthogonal behaviors defined by template parameters:

```cpp
template <typename OutputPolicy>
class Logger : private OutputPolicy {
public:
    void log(const std::string& msg) {
        OutputPolicy::write("[LOG]: " + msg);
    }
};

struct ConsolePolicy {
    void write(const std::string& msg) { std::cout << msg << "\n"; }
};

struct FilePolicy {
    void write(const std::string& msg) { /* Write to file stream */ }
};

using ConsoleLogger = Logger<ConsolePolicy>;
```

---

## 💡 Key Interview Misconceptions & Traps in Tier 10

1. **Misconception**: `std::unique_ptr` inside a Pimpl class can use `= default` destructor in the header file.  
   * *Truth*: **FALSE!** In `Widget.h`, `Implementation` is an incomplete type. Generating `~Widget() = default` in the header causes a compilation error because `std::default_delete<Implementation>` requires a complete type definition! Declare `~Widget();` in the header and define `Widget::~Widget() = default;` in `Widget.cpp`.
