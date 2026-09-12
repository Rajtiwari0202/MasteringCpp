# 🔬 Tier 5: Modern C++ Mechanics (C++11 through C++23)

> **Architect's Perspective**: Modern C++ is not merely syntactic sugar—it is a total paradigm shift toward RAII, compile-time computation (`constexpr`/`consteval`), zero-allocation views (`string_view`/`span`), type safety (`variant`/`optional`), and zero-overhead move abstractions.

---

## 1. Move Semantics & Perfect Forwarding

### Move Semantics Mechanics
Move semantics allows transferring ownership of dynamically allocated heap resources from a temporary object (Xvalue/PRvalue) to a destination object without copying buffer bytes!

```cpp
class DynamicBuffer {
    size_t m_size;
    int* m_data;

public:
    // Move Constructor: Steal buffer pointer and reset source object!
    DynamicBuffer(DynamicBuffer&& other) noexcept 
        : m_size(other.m_size), m_data(other.m_data) {
        other.m_size = 0;
        other.m_data = nullptr; // Crucial: prevents double-free in ~DynamicBuffer()
    }
};
```

---

### Universal References & Perfect Forwarding (`std::forward`)
A reference declared as `T&&` in a **template type deduction context** is a **Universal Reference** (or Forwarding Reference). It can bind to both Lvalues and Rvalues!

```cpp
template <typename T>
void wrapper(T&& arg) {
    // std::forward<T> preserves the EXACT original value category (Lvalue stays Lvalue, Rvalue stays Rvalue)
    targetFunction(std::forward<T>(arg));
}
```

---

## 2. Type Deduction Taxonomy

### `auto` vs `decltype(expr)` vs `decltype(auto)`

1. **`auto`**: Deduces type using template argument deduction rules. **Strips top-level `const` and reference qualifiers!**
   ```cpp
   const int& x = 10;
   auto a = x; // Type is 'int' (const and & stripped!)
   const auto& b = x; // Type is 'const int&'
   ```

2. **`decltype(expr)`**: Inspects the exact declared type of an expression **WITHOUT evaluating the expression**! Preserves references and `const`.
   ```cpp
   int y = 42;
   decltype(y) t1; // Type is 'int'
   decltype((y)) t2 = y; // Double parens makes it an Lvalue expression -> Type is 'int&'!
   ```

3. **`decltype(auto)`** (C++14): Deduces return type using `decltype` rules, perfectly preserving references and constness automatically.

---

## 3. Lambda Expressions & Underlying Compiler Layout

When you write a Lambda expression, the compiler transforms it into an anonymous **Closure Object** (a struct with an overloaded `operator()`):

```cpp
int factor = 2;
auto lambda = [factor](int x) { return x * factor; };
```

#### Equivalent Compiler Code Generation:
```cpp
struct AnonymousClosure {
    int factor; // Captured member
    AnonymousClosure(int f) : factor(f) {}

    int operator()(int x) const { // const by default!
        return x * factor;
    }
};
```

### Lambda Capture Modes:
* `[=]`: Capture all outer variables by Value.
* `[&]`: Capture all outer variables by Reference.
* `[x, &y]`: Explicit capture.
* `[ptr = std::move(ptr)]` (C++14 Init Capture): Move an object into closure state!
* `mutable` keyword: Allows modifying values captured by value inside `operator()`.

### Lambda Performance: Stateless Lambda vs `std::function`
* **Stateless Lambda / Custom Lambda**: Inlines directly at assembly level. **Zero runtime overhead!**
* **`std::function<T>`**: Wraps any callable using **Type Erasure**. Requires virtual-like pointer indirection call and heap allocation if closure size exceeds small buffer optimization (SBO) threshold (~32 bytes).

---

## 4. Compile-Time Calculation: `constexpr`, `consteval` & `constinit`

| Keyword | Introduced | Behavior & Guarantee |
| :--- | :--- | :--- |
| **`constexpr`** | C++11 | Evaluates at **compile-time if arguments are constant**, OR executes as normal runtime function if arguments are non-constant. |
| **`consteval`** | C++20 | **Immediate Function**: GUARANTEED to execute ONLY at compile-time. Triggers compile error if invoked with runtime variables! |
| **`constinit`** | C++20 | Ensures a static or thread-local variable is **initialized at compile-time**, preventing the Static Initialization Order Fiasco. |

---

## 5. Modern Vocabulary Types & Zero-Allocation Views

### 1. `std::optional<T>`
Encapsulates a value that may or may not exist without using dynamic raw pointers or sentinel values (`-1`).

### 2. `std::variant<Ts...>` & `std::visit`
Type-safe tagged union replacing unsafe C `union`. Supports pattern matching via `std::visit`:

```cpp
std::variant<int, double, std::string> data = "Hello C++20";

std::visit([](auto&& arg) {
    std::cout << "Visited: " << arg << "\n";
}, data);
```

### 3. `std::string_view` & `std::span<T>` (C++20)
* **`std::string_view`**: A non-owning 16-byte view (Pointer + Length) of any string buffer (`const char*`, `std::string`, `char[]`). Passing `string_view` eliminates heap allocations during string slicing!
* **`std::span<T>`**: A non-owning contiguous memory view over C arrays, `std::vector`, or `std::array`.

---

## 💡 Key Interview Misconceptions & Traps in Tier 5

1. **Misconception**: `std::string_view` keeps the underlying string memory alive.  
   * *Truth*: `string_view` is a non-owning view! If the original string is destroyed or modified, the `string_view` becomes a **dangling reference**, causing Undefined Behavior!

2. **Misconception**: Lambda functions captured by `[&]` are safe to pass to async threads.  
   * *Truth*: Capturing by reference `[&]` when the closure outlives local stack variables causes catastrophic stack memory use-after-free bugs in multithreaded code! Always capture by value `[=]` or move `[x = std::move(x)]` for async tasks.
