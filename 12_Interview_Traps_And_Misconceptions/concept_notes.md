# 🔬 Tier 11: High-Frequency Technical Interview Traps, Exception Safety & Undefined Behavior (UB)

> **Architect's Perspective**: Top-tier tech company interviewers (Google, Meta, Apple, Citadel, Jane Street) use edge-case questions to test whether a candidate truly understands how C++ code interacts with the compiler optimizer and CPU memory model.

---

## 1. The C++ Undefined Behavior (UB) Catalog

Undefined Behavior means **ANYTHING CAN HAPPEN**. The compiler assumes UB never occurs in valid code, allowing it to strip bounds checks, reorder instructions, or generate corrupted machine code.

### 10 Critical Undefined Behaviors:

1. **Signed Integer Overflow**: `INT_MAX + 1` is UB. (Unsigned overflow `UINT_MAX + 1 == 0` is defined).
2. **Strict Aliasing Rule Violation**: Dereferencing a pointer of type `T1*` pointing to memory holding `T2` (e.g. `float* f = (float*)&int_val; *f = 1.0f;`).
3. **Null Pointer Dereference**: `int* p = nullptr; *p = 10;`.
4. **Use-After-Free & Dangling References**: Returning a reference to a local stack variable or accessing memory after `delete`.
5. **Array Out-Of-Bounds Access**: Reading or writing past array bounds (`arr[N]`).
6. **Modifying a `const` Object**: Using `const_cast<T*>` to modify a variable declared `const`.
7. **Deleting Derived Object via Non-Virtual Base Pointer**: `Base* b = new Derived(); delete b;` where `Base::~Base()` is non-virtual.
8. **Double Free / Mismatched Array Deallocation**: Calling `delete` instead of `delete[]` on array memory allocated with `new T[]`.
9. **Data Races**: Concurrent non-atomic read/write across threads without mutex synchronization.
10. **Uninitialized Variable Reads**: Accessing local scalar variables before initialization (`int x; int y = x + 5;`).

---

## 2. Exception Safety Guarantees

Every function in robust C++ libraries must provide one of 4 Exception Safety Guarantees:

```
[ Nothrow Guarantee ] > [ Strong Guarantee ] > [ Basic Guarantee ] > [ No Guarantee ]
```

### 1. Nothrow / No-Fail Guarantee (`noexcept`)
The function is strictly guaranteed never to throw an exception under any circumstances.
* **Failure Penalty**: If a function marked `noexcept` throws an unhandled exception, `std::terminate()` is called immediately!
* **Required For**: Move constructors, move assignment operators, and swap functions! (Without `noexcept`, `std::vector` falls back to copying during reallocation!).

### 2. Strong Exception Guarantee (Transactional)
If the function throws an exception, **the program state remains completely unchanged**, as if the function had never been called! (Commit or Rollback semantics).
* Implemented via **Copy-and-Swap Idiom**.

### 3. Basic Exception Guarantee
If the function throws an exception, no resources/memory are leaked, and objects remain in a valid (though unpredicted) state.

### 4. No Exception Guarantee
If an exception occurs, memory is leaked, objects are left corrupted, or program invariants are destroyed. (Unacceptable in production code!).

---

## 3. Top 5 Interview Gotchas & Code Traps

### Trap 1: The Static Initialization Order Fiasco
When static objects in separate Translation Units depend on each other, their initialization order is **UNDEFINED**!
* **Fix**: Replace global static objects with **Meyers Singletons** (static local variables inside functions)!

### Trap 2: Infinite Loop with Unsigned Integers
```cpp
// TRAP: 'i >= 0' is ALWAYS true for unsigned int! Loops infinitely!
for (unsigned int i = 10; i >= 0; --i) {
    std::cout << i << "\n";
}
```

### Trap 3: Lambda Reference Capture Outliving Stack Scope
```cpp
auto getDanglingLambda() {
    int secret = 42;
    return [&secret]() { return secret; }; // TRAP: 'secret' stack memory destroyed on return!
}
```

### Trap 4: Vector Iterator Invalidation during Loop
```cpp
std::vector<int> vec = {1, 2, 3, 4};
for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (*it == 2) vec.push_back(99); // TRAP: push_back reallocates vector memory, invalidating 'it'!
}
```

### Trap 5: `std::size()` Unsigned Underflow
```cpp
std::vector<int> vec;
// TRAP: 'vec.size() - 1' wraps around to UINT64_MAX when vec is empty!
for (int i = 0; i < vec.size() - 1; ++i) { ... }
```

---

## 💡 Key Interview Misconceptions & Traps in Tier 11

1. **Misconception**: `catch (...)` handles hardware operating system crashes like Segmentation Faults or Divide-by-Zero.  
   * *Truth*: **FALSE!** Standard C++ exceptions handle software `throw` statements ONLY. OS hardware traps (Segmentation Fault, Access Violation, Bus Error) bypass C++ exception handlers completely and kill the process!

2. **Misconception**: `noexcept` speeds up code execution.  
   * *Truth*: **TRUE!** Marking functions `noexcept` allows the compiler to omit exception-unwinding stack tables (`.eh_frame`), reducing binary code size and allowing aggressive loop optimizations and `std::vector` move operations!
