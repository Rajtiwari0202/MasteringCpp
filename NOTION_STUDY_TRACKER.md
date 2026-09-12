# 🚀 C++ Zero-to-Hero Master Study Tracker (Notion Template)

> **Instructions for Notion**:
> Select all text in this document (`Ctrl + A`), copy (`Ctrl + C`), and paste (`Ctrl + V`) directly into a blank Notion page. Notion will automatically convert these into interactive checkboxes, toggles, and tables!

---

## 📊 Overall Progress Dashboard

- [ ] **Tier 0: Toolchains, Compilation Pipeline & Assembly Analysis** (0 / 5 Completed)
- [ ] **Tier 1: Core Primitives, Hardware Memory Layout & Bits** (0 / 5 Completed)
- [ ] **Tier 2: Pointers, References & Value Categories** (0 / 5 Completed)
- [ ] **Tier 3: OOP, Virtual Tables (Vtables) & Object Layout** (0 / 5 Completed)
- [ ] **Tier 4: Dynamic Memory, Smart Pointers & Custom Allocators** (0 / 5 Completed)
- [ ] **Tier 5: Modern C++ Features (C++11 to C++23)** (0 / 5 Completed)
- [ ] **Tier 6: STL Containers, Hash Tables & C++20 Ranges** (0 / 5 Completed)
- [ ] **Tier 7: Templates, SFINAE & C++20 Concepts** (0 / 5 Completed)
- [ ] **Tier 8: Systems OS, Virtual Memory & Cache Hierarchy** (0 / 5 Completed)
- [ ] **Tier 9: Concurrency, Atomics & Lock-Free SPSC Queues** (0 / 5 Completed)
- [ ] **Tier 10: Advanced Design Patterns & Architecture** (0 / 5 Completed)
- [ ] **Tier 11: Interview Traps & Undefined Behavior Catalog** (0 / 5 Completed)
- [ ] **Capstone Projects: Production Engine Allocator** (0 / 3 Completed)

---

## ⚡ Daily Study Workflow (5-Step Algorithm)

1. 📖 **Step 1: Read Theory Notes** (`0X_Module/concept_notes.md`)  
   Understand the architectural rationale, CPU memory layout diagrams, and key misconceptions.
2. 💻 **Step 2: Compile & Run Code Demos** (`0X_Module/01_..._demo.cpp`)  
   Compile using `g++ -Wall -Wextra -std=c++20` and observe the exact runtime output.
3. 🔬 **Step 3: Inspect Tooling & Assembly**  
   Run `nm` or `objdump` to view mangled symbols or Godbolt to inspect generated assembly.
4. 🧠 **Step 4: Solve Interview Trap Quizzes**  
   Test yourself on edge-case misconceptions at the end of each module note.
5. ✅ **Step 5: Mark Completed & Set Revision Date** (1-Day, 7-Day, 30-Day Spaced Repetition).

---

## 📝 Detailed Module Checklists

### 🔹 Tier 0: Toolchains, Compilation Pipeline & Assembly Analysis
*Folder: `01_Compilation_Toolchains_Assembly/`*

- [ ] **0.1 Preprocessing Phase** — Macro expansion, `#include` include guards vs `#pragma once`, stringification `#`, token concatenation `##`, `#ifdef`.
- [ ] **0.2 Compilation Phase** — AST parsing, IR optimization passes (`-O0` to `-O3`, `-flto`), inline expansion.
- [ ] **0.3 Symbol Mangling & Linkage** — Inspect mangled C++ symbols via `nm`, implement `extern "C"` export block.
- [ ] **0.4 Object Files & Linker** — ELF/PE-COFF sections (`.text`, `.data`, `.bss`), ODR violations, static vs dynamic libraries.
- [ ] **0.5 Tooling & Sanitizers** — Compile with ASan (`-fsanitize=address`) & UBSan (`-fsanitize=undefined`).

---

### 🔹 Tier 1: Core Primitives, Hardware Memory Layout & Bits
*Folder: `02_Memory_Layout_And_Primitives/`*

- [ ] **1.1 Virtual Memory Address Spaces** — Stack (downward), Heap (upward), Data, BSS, Text/Code segments.
- [ ] **1.2 Integer Representation** — Two's complement, signed overflow (UB) vs unsigned wrapping (modulo $2^N$).
- [ ] **1.3 IEEE 754 Floating Point** — Sign (1b), Exponent (8b), Mantissa (23b), precision loss, `NaN != NaN`, `-0.0`.
- [ ] **1.4 Structure Alignment & Padding** — Calculate `offsetof`, optimize member layout, `#pragma pack`.
- [ ] **1.5 Cache Line Isolation** — `alignof` and `alignas(64)` for cache-line boundaries.

---

### 🔹 Tier 2: Pointers, References & Value Categories
*Folder: `03_Pointers_References_Value_Categories/`*

- [ ] **2.1 Pointer Mechanics** — Pointer arithmetic scaling by `sizeof(T)`, `void*`, `std::nullptr_t`.
- [ ] **2.2 Reference Mechanics** — Lifetime extension of temporary PRvalues bound to `const T&`.
- [ ] **2.3 Expression Value Categories** — Identify Lvalues, PRvalues, Xvalues, GLvalues, Rvalues.
- [ ] **2.4 Reference Collapsing** — Apply `& + & -> &`, `& + && -> &`, `&& + && -> &&` collapse rules.
- [ ] **2.5 Pointers to Members** — Synthesize member variable (`T::*`) and member function pointers (`.*` and `->*`).

---

### 🔹 Tier 3: OOP, Virtual Tables (Vtables) & Object Layout
*Folder: `04_OOP_Vtables_And_Memory_Layout/`*

- [ ] **3.1 Special Member Functions** — Rule of 0 / 3 / 5, explicit constructors, `mutable` keyword.
- [ ] **3.2 Vtable & Vptr Architecture** — Calculate hidden `vptr` size overhead, virtual call indirect branch cost.
- [ ] **3.3 Multiple Inheritance Layout** — Observe pointer address offset shift when casting `Derived*` to `Base2*`.
- [ ] **3.4 Diamond Inheritance Fix** — Virtual base classes (`virtual public Base`), `vbase_offset` table overhead.
- [ ] **3.5 Object Slicing Trap** — Prevent slicing by passing polymorphic objects via reference/smart pointers.

---

### 🔹 Tier 4: Dynamic Memory, Smart Pointers & Custom Allocators
*Folder: `05_Smart_Pointers_And_RAII/`*

- [ ] **4.1 Low-Level Allocation** — `malloc`/`free` vs `new`/`delete`, placement `new`, explicit `~T()` destructor calls.
- [ ] **4.2 `std::unique_ptr<T>`** — Exclusive ownership, move-only, custom deleters, zero overhead.
- [ ] **4.3 `std::shared_ptr<T>`** — Control block layout (strong count, weak count, deleter), atomic ref counts.
- [ ] **4.4 `std::weak_ptr<T>`** — Break circular reference deadlocks, lock via `.lock()`.
- [ ] **4.5 Allocation Overhead** — `std::make_shared` single block vs `shared_ptr(new T)`.

---

### 🔹 Tier 5: Modern C++ Features (C++11 through C++23)
*Folder: `06_Modern_Cpp_11_to_23/`*

- [ ] **5.1 Move Semantics & Forwarding** — `std::move` static cast, universal references (`T&&`), `std::forward`.
- [ ] **5.2 Type Deduction** — `auto` stripping rules vs `decltype(expr)` vs `decltype(auto)`.
- [ ] **5.3 Lambda Closure Mechanics** — Value/Reference captures, init captures (`[ptr = std::move(ptr)]`), `mutable`.
- [ ] **5.4 Compile-Time Calculations** — `constexpr` vs `consteval` (immediate functions) vs `constinit`.
- [ ] **5.5 Vocabulary Types** — `std::optional`, `std::variant`/`std::visit`, zero-allocation `string_view` & `span`.

---

### 🔹 Tier 6: STL Containers, Hash Tables & C++20 Ranges
*Folder: `07_STL_Deep_Dive_And_Iterators/`*

- [ ] **6.1 `std::vector` Mechanics** — Pointer triple (`m_start`, `m_finish`, `m_end`), 1.5x/2.0x growth factors, `shrink_to_fit()`.
- [ ] **6.2 Container Overheads** — `std::deque` block map, `std::list` node pointer chasing, `std::map` Red-Black tree.
- [ ] **6.3 Hash Table Internals** — `std::unordered_map` separate chaining buckets, load factor, rehash passes.
- [ ] **6.4 C++20 Ranges & Views** — Composable lazy evaluation pipelines using `views::filter | views::transform`.
- [ ] **6.5 Custom Iterators** — Implement custom range iterator class adhering to `std::forward_iterator_tag`.

---

### 🔹 Tier 7: Templates, SFINAE & C++20 Concepts
*Folder: `08_Templates_And_Metaprogramming/`*

- [ ] **7.1 Template Specialization** — Class template full vs partial specialization rules.
- [ ] **7.2 SFINAE Mechanics** — Overload resolution filtering via `std::enable_if_t`.
- [ ] **7.3 Member Detection** — Implement `std::void_t` compile-time member method detector.
- [ ] **7.4 C++20 Concepts** — Define custom `concept` with simple/type/compound `requires` clauses.
- [ ] **7.5 Variadic Fold Expressions** — Binary left folds `(... + args)` & comma operator expansion.

---

### 🔹 Tier 8: Systems OS, Virtual Memory & Cache Hierarchy
*Folder: `09_Systems_OS_And_Hardware/`*

- [ ] **8.1 OS Virtual Memory** — Page tables, TLB, zero-copy file mapping via POSIX `mmap` / Win32 `VirtualAlloc`.
- [ ] **8.2 CPU Cache Hierarchy** — L1d/L1i, L2, L3 latency, 64-byte cache line prefetching.
- [ ] **8.3 Cache Miss Benchmark** — Benchmark contiguous array vector vs fragmented pointer chasing.
- [ ] **8.4 False Sharing Fix** — Isolate multi-threaded atomic counters using `alignas(64)`.
- [ ] **8.5 Data-Oriented Design** — Array-of-Structures (AoS) vs Structure-of-Arrays (SoA) SIMD layout.

---

### 🔹 Tier 9: Concurrency, Atomics & Lock-Free SPSC Queues
*Folder: `10_Concurrency_And_LockFree/`*

- [ ] **9.1 Thread Synchronization** — `std::jthread`, `std::shared_mutex` (RW Lock), `std::scoped_lock` deadlock avoidance.
- [ ] **9.2 Condition Variables** — Spurious wakeup prevention using predicate loop `cv.wait(lock, pred)`.
- [ ] **9.3 Atomics & CAS** — `std::atomic<T>`, `compare_exchange_weak` vs `compare_exchange_strong`.
- [ ] **9.4 Memory Ordering** — `relaxed` vs `acquire`/`release` synchronization barriers vs `seq_cst`.
- [ ] **9.5 Lock-Free SPSC Queue** — Implement atomic head/tail ring buffer with zero mutex locks.

---

### 🔹 Tier 10: Advanced Design Patterns & Architecture
*Folder: `11_Design_Patterns_And_Architecture/`*

- [ ] **10.1 Meyers Singleton** — C++11 thread-safe static local initialization guarantee.
- [ ] **10.2 Pimpl Idiom** — Build compilation firewall hiding implementation headers in `.cpp`.
- [ ] **10.3 CRTP Static Polymorphism** — Inlined static dispatch via `class Derived : public Base<Derived>`.
- [ ] **10.4 Policy-Based Design** — Decompose class behavior into policy template parameters.

---

### 🔹 Tier 11: Technical Interview Traps & Undefined Behavior Catalog
*Folder: `12_Interview_Traps_And_Misconceptions/`*

- [ ] **11.1 Undefined Behavior Catalog** — Strict aliasing violations, signed overflow, dangling refs, null dereferences.
- [ ] **11.2 Exception Safety Guarantees** — Nothrow (`noexcept`), Strong (Copy-and-Swap), Basic, No Guarantee.
- [ ] **11.3 Safe Bit Aliasing** — Type-safe bit reinterpretation using `std::bit_cast` (C++20).
- [ ] **11.4 Copy-and-Swap Idiom** — Implement transactional strong exception safety assignment operator.

---

### 🛠️ Capstone Projects Checklist
*Folder: `Capstone_Projects/`*

- [ ] **Project 1: High-Performance Custom Memory Allocator**  
  - [ ] Implement `ArenaBumpAllocator` (Bump pointer, O(1) allocation/bulk reset).  
  - [ ] Implement `FixedPoolAllocator` (Free-list stack, O(1) recycling).  
  - [ ] Test allocation alignment and zero memory leaks.

---

## 🗓️ Spaced Repetition Revision Log

| Module | First Study Date | 1-Day Review | 7-Day Review | 30-Day Review | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Tier 0: Toolchains** | | | | | ⏳ Pending |
| **Tier 1: Primitives & Bits** | | | | | ⏳ Pending |
| **Tier 2: Pointers & Value Categories** | | | | | ⏳ Pending |
| **Tier 3: OOP & Vtables** | | | | | ⏳ Pending |
| **Tier 4: Smart Pointers** | | | | | ⏳ Pending |
| **Tier 5: Modern C++** | | | | | ⏳ Pending |
| **Tier 6: STL & Ranges** | | | | | ⏳ Pending |
| **Tier 7: Templates & Concepts** | | | | | ⏳ Pending |
| **Tier 8: OS Systems & Hardware** | | | | | ⏳ Pending |
| **Tier 9: Concurrency & Lock-Free** | | | | | ⏳ Pending |
| **Tier 10: Design Patterns** | | | | | ⏳ Pending |
| **Tier 11: Interview Traps** | | | | | ⏳ Pending |
| **Capstone 1: Custom Allocator** | | | | | ⏳ Pending |
