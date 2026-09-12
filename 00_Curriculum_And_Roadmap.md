# 🚀 Ultimate C++ Master Curriculum: Zero to Hero (Systems, Modern C++, Memory & Hard Interview Mastery)

> **Welcome to your ultimate C++ Master Repository.**  
> This directory is structured to take you from core mechanics to **elite system programming**, **hardware-level understanding**, **template metaprogramming**, **modern C++ (up to C++20/23)**, **lock-free concurrency**, and **top-tier technical interview preparation** (Google, Meta, NVIDIA, Apple, HFTs like Citadel/Jane Street).

---

## 🧭 Repository Structure Strategy

To keep your workspace clean, organized, and easily searchable for revision:

```
C++ full course/
├── 00_Curriculum_And_Roadmap.md               <-- You are here (Master Index)
├── 01_Compilation_Toolchains_Assembly/         <-- Preprocessing, Compiler IR, Linking, Symbol Mangling, Assembly
├── 02_Memory_Layout_And_Primitives/            <-- Stack/Heap/BSS/Data, Floating Point, Alignment, Bitfields, Padding
├── 03_Pointers_References_Value_Categories/    <-- Raw Pointers, L/Rvalues, Xvalues, PRvalues, Reference Collapsing
├── 04_OOP_Vtables_And_Memory_Layout/           <-- Vtables, Vptrs, Virtual Inheritance, Rule of 0/3/5, Object Slicing
├── 05_Smart_Pointers_And_RAII/                 <-- Unique/Shared/Weak Pointers, Control Block layout, Custom Allocators
├── 06_Modern_Cpp_11_to_23/                     <-- Move Semantics, Lambdas, Constexpr, Views, Optional, Variant, Span
├── 07_STL_Deep_Dive_And_Iterators/             <-- Vector mechanics, RB-Trees, Hash Tables, Iterators, Custom Allocators
├── 08_Templates_And_Metaprogramming/           <-- SFINAE, Concepts, Variadic Templates, Fold Expressions, Type Traits
├── 09_Systems_OS_And_Hardware/                 <-- Memory mapping (mmap), Cache Lines, False Sharing, DOD, Inline Assembly
├── 10_Concurrency_And_LockFree/                <-- Mutexes, Condition Variables, Atomics, C++ Memory Model, SPSC Queues
├── 11_Design_Patterns_And_Architecture/        <-- Meyers Singleton, Pimpl, CRTP, Factory, Policy-based Design
├── 12_Interview_Traps_And_Misconceptions/      <-- Hard Interview Edge-Cases, UB Catalog, Exception Safety Guarantees
├── 00_Legacy_Practice/                         <-- Initial practice scripts (2sum, snake, linkedlist, etc.)
└── Capstone_Projects/                          <-- Production-grade custom allocators, lock-free ring buffer, key-value engine
```

---

## 📚 Detailed 11-Tier Curriculum Roadmap

---

### 🔹 TIER 0: Toolchain, Compilation Pipeline & Assembly Analysis
**Objective**: Understand what happens from `main.cpp` to binary execution.

- **Compilation Pipeline**:
  - Preprocessor (`g++ -E`): Macro expansion, `#include` mechanics, include guards (`#pragma once`).
  - Compiler (`g++ -S`): Abstract Syntax Tree (AST), Intermediate Representation (IR), Assembly code generation.
  - Assembler (`g++ -c`): Translating assembly to Object Files (`.o` / `.obj`).
  - Linker: Static linking (`.a` / `.lib`) vs Dynamic linking (`.so` / `.dll`).
- **Symbols & Linkage**:
  - Symbol mangling (Name decoration) & `extern "C"`.
  - Strong vs Weak symbols (`__attribute__((weak))`).
  - One Definition Rule (ODR) violations and linkage types (Internal vs External vs No linkage).
- **Tooling & Sanitizers**:
  - GCC/Clang optimization flags (`-O0`, `-O2`, `-O3`, `-OFast`, `-flto`).
  - AddressSanitizer (`-fsanitize=address`), ThreadSanitizer (`-fsanitize=thread`), UndefinedBehaviorSanitizer (`-fsanitize=undefined`).
  - Godbolt / Compiler Explorer workflow for assembly optimization inspection.

---

### 🔹 TIER 1: Core Primitives, Hardware Memory Layout & Bits
**Objective**: Understand how data lives in silicon, memory registers, and RAM.

- **Memory Segment Architecture**:
  - Stack (Automatic allocation, stack pointer, call frames).
  - Heap (Dynamic allocation, heap fragmenting).
  - Data Segment (Initialized globals & statics).
  - BSS Segment (Uninitialized globals & statics).
  - Text / Code Segment (Read-only instructions).
- **Data Types & Bit Level Representation**:
  - Signed vs Unsigned integers, Two's complement representation.
  - Signed integer overflow (Undefined Behavior) vs Unsigned overflow (Defined modulo wrapping).
  - IEEE 754 Floating-Point Standard: Sign, Exponent, Mantissa, Precision loss, Denormal/Subnormal numbers, `-0.0`, `NaN`, `Infinity`.
- **Memory Alignment & Structure Layout**:
  - Memory alignment rules (natural alignment requirements of CPUs).
  - Structure padding, member ordering optimization, `#pragma pack`.
  - `alignof` and `alignas` keywords.
  - Bit manipulation tricks: Bitmasks, bitwise operations (`&`, `|`, `^`, `~`, `<<`, `>>`), bitfields in structs.

---

### 🔹 TIER 2: Pointers, References & Value Categories
**Objective**: Master indirect memory access and expression taxonomy.

- **Pointer & Reference Mechanics**:
  - Raw pointers, pointer arithmetic (`ptr + 1` scaling by `sizeof(T)`), pointer-to-pointer (`T**`).
  - `void*` raw memory pointers, `std::nullptr_t` vs `NULL` vs `0`.
  - Reference types (`T&`, `const T&`), reference lifetime extensions.
  - Pointer to member functions & variables (`T::*`).
- **Value Categories (Expression Taxonomy)**:
  - Expression properties: Has identity vs Can be moved from.
  - **Lvalues**: Expressions with persistent identity whose address can be taken.
  - **PRvalues** (Pure Rvalues): Temporary values, literals, return-by-value functions.
  - **Xvalues** (eXpiring values): Objects near end of lifetime (e.g., `std::move(x)`).
  - **GLvalues** (Generalized Lvalues) = Lvalues + Xvalues.
  - **Rvalues** = PRvalues + Xvalues.
  - Reference Collapsing Rules (`& + & -> &`, `& + && -> &`, `&& + && -> &&`).

---

### 🔹 TIER 3: Object-Oriented Programming & Low-Level Memory Layout
**Objective**: Master class layout, virtual dispatch, and object lifetimes.

- **Class Foundations**:
  - Constructors, Destructors, Copy Constructor, Copy Assignment Operator.
  - Move Constructor, Move Assignment Operator.
  - The **Rule of 0 / 3 / 5**.
  - `explicit` constructors (preventing implicit conversions), `const` member functions, `mutable` members.
- **Inheritance & Virtual Tables (Vtables)**:
  - Single Inheritance memory layout.
  - Multiple Inheritance memory layout & multiple `vptr` offsets.
  - **Diamond Inheritance**: Problems with multiple base copies & **Virtual Base Classes** (`virtual inheritance`) layout overhead.
  - Virtual Table (`vtable`) and Virtual Pointer (`vptr`) mechanics under the hood.
  - Virtual Function Call Cost: Indirect branch, cache miss penalty, compiler devirtualization.
  - `override` and `final` qualifiers.
- **Object Lifetime & Storage**:
  - Object Slicing trap when copying derived objects by value.
  - Static member initialization, static local variable lazy initialization (Meyers thread safety guarantee).

---

### 🔹 TIER 4: Dynamic Memory Management, Smart Pointers & Custom Allocators
**Objective**: Zero memory leaks, zero dangling pointers, custom allocation strategies.

- **Manual Memory Allocation**:
  - `malloc` / `free` vs `new` / `delete` vs `new[]` / `delete[]`.
  - **Placement `new`**: Constructing objects in pre-allocated memory buffers.
  - Calling destructors explicitly (`ptr->~T()`).
- **Smart Pointers Deep Dive**:
  - `std::unique_ptr<T>`: Single ownership, move-only, zero runtime overhead, custom deleters.
  - `std::shared_ptr<T>`: Shared ownership, control block memory layout (strong ref count, weak ref count, deleter, allocator).
  - `std::weak_ptr<T>`: Non-owning observer, breaking circular reference deadlocks (`lock()` method).
  - `std::make_unique` vs `std::make_shared`: Allocation efficiency, exception safety, control block lifetime implications.
- **Custom Memory Allocator Architecture**:
  - **Arena / Linear Allocator**: Blazing fast bump-pointer allocation for scratch memory.
  - **Pool Allocator**: O(1) allocation/deallocation for fixed-size object nodes.
  - **Stack Allocator**: Scope-bound LIFO memory management.

---

### 🔹 TIER 5: Modern C++ Fundamentals (C++11 through C++23)
**Objective**: Write expressive, clean, high-performance modern C++ code.

- **Move Semantics & Rvalue References**:
  - `std::move` (unconditional cast to rvalue) vs `std::forward` (conditional cast for perfect forwarding).
  - Universal References / Forwarding References (`auto&&` and `T&&` in template context).
- **Type Deduction**:
  - `auto` type deduction rules (strip references and top-level `const`).
  - `decltype(expr)` vs `decltype(auto)`.
- **Lambda Expressions**:
  - Capture modes: `[=]`, `[&]`, `[x, &y]`, Init captures (`[ptr = std::move(ptr)]`).
  - `mutable` lambdas, generic lambdas (`[](auto x)`), template lambdas (C++20).
  - `std::function` overhead (type erasure, heap allocation) vs raw Lambdas vs Function Pointers.
- **Compile-Time Execution & Compile-Time Constants**:
  - `constexpr` functions and constructors.
  - `consteval` (immediate functions, guaranteed compile-time execution in C++20).
  - `constinit` (guaranteed compile-time initialization of static/thread-local variables in C++20).
- **Modern Vocabulary Types & Abstractions**:
  - `std::optional<T>`: Expressing optional values without nullptr pointers.
  - `std::variant<Ts...>`: Type-safe tagged union & `std::visit` pattern.
  - `std::any`: Type-safe container for single values of any type.
  - `std::string_view`: Non-owning view of string buffer (zero-allocation slicing).
  - `std::span<T>` (C++20): Non-owning view of contiguous sequence.

---

### 🔹 TIER 6: Standard Template Library (STL) Deep Dive & Algorithmic Complexity
**Objective**: Master STL internals, time complexity, memory characteristics, and iterator invalidation.

- **Sequence Containers**:
  - `std::vector`: Internal layout (`capacity`, `size`, pointer triple), growth factor (1.5x MSVC vs 2.0x GCC), reallocation costs, `reserve()` vs `resize()`, iterator invalidation rules.
  - `std::deque`: Block map array layout, random access performance vs vector.
  - `std::list` / `std::forward_list`: Doubly/singly linked list node overhead, pointer chasing, cache unfriendliness.
  - `std::array`: Stack-allocated fixed-size contiguous array.
- **Associative Containers**:
  - `std::map` / `std::set` / `std::multimap` / `std::multiset`: Self-balancing Red-Black Tree implementation, O(log N) lookup/insert, iterator stability.
- **Unordered Associative Containers**:
  - `std::unordered_map` / `std::unordered_set`: Separate chaining Hash Table implementation, hash collision handling, load factor, rehash cost, writing custom hash functions (`std::hash<T>`).
- **Container Adaptors**:
  - `std::stack`, `std::queue`, `std::priority_queue` (heap layout via `std::make_heap`).
- **Iterators & C++20 Ranges**:
  - Iterator categories: Input, Output, Forward, Bidirectional, Random Access, Contiguous.
  - Custom iterator implementation (`iterator_traits`).
  - **C++20 Ranges & Views**: Composable pipelines using binary pipe `|` operator (`views::filter`, `views::transform`).

---

### 🔹 TIER 7: Generic Programming, Templates & Metaprogramming (TMP)
**Objective**: Master compile-time code generation, type manipulation, and static dispatch.

- **Template Basics**:
  - Function templates, class templates, alias templates (`using`).
  - Template argument deduction, explicit instantiation.
  - Full specialization vs Partial specialization.
  - Non-type template parameters (NTTP) including class types in C++20.
- **SFINAE (Substitution Failure Is Not An Error)**:
  - `std::enable_if` / `std::enable_if_t`.
  - `std::void_t` trick for inspecting class members at compile time.
  - Expressions in `decltype` for SFINAE checks.
- **C++20 Concepts & Constraints**:
  - Concept definitions (`template <typename T> concept...`).
  - `requires` clauses (nested requires, simple requires, compound requires, type requires).
  - Constraining functions and template classes without ugly SFINAE errors.
- **Variadic Templates & Modern TMP**:
  - Parameter packs (`typename... Args`), pack expansion.
  - Fold expressions (C++17): Left fold `(... + args)`, Right fold `(args + ...)`.
  - Type Traits (`std::is_same_v`, `std::is_constructible_v`, `std::remove_reference_t`, custom type traits).

---

### 🔹 TIER 8: Systems Programming, OS Integration & Hardware Mechanics
**Objective**: Connect C++ directly to CPU architecture, operating system kernels, and high-performance hardware.

- **Virtual Memory & OS Kernels**:
  - Virtual address space, Page Tables, Translation Lookaside Buffer (TLB), Page Faults.
  - OS memory allocation APIs: `mmap` / `munmap` (Linux/POSIX) and `VirtualAlloc` / `VirtualFree` (Windows).
  - Memory-mapped files for high-throughput I/O.
- **Hardware Caching & Data-Oriented Design (DOD)**:
  - CPU Cache Hierarchy: L1 (Data/Instruction), L2, L3 caches.
  - Cache Line size (typically 64 bytes), Cache Hits vs Cache Misses.
  - **False Sharing**: Multiple threads modifying adjacent variables on the same cache line (`alignas(std::hardware_destructive_interference_size)`).
  - Structure-of-Arrays (SoA) vs Array-of-Structures (AoS) for SIMD vectorization.
- **Low-Level Execution Control**:
  - Inline Assembly (`asm` / `__asm__`).
  - The `volatile` qualifier: preventing compiler reordering for memory-mapped hardware I/O (NOT for thread synchronization!).
  - Undefined Behavior (UB) catalog: Strict aliasing violations (`reinterpret_cast` trap), uninitialized reads, out-of-bound access, data races.

---

### 🔹 TIER 9: Concurrency, Multithreading & Lock-Free Low-Latency Programming
**Objective**: Build safe, high-throughput multi-threaded systems and lock-free data structures.

- **Thread Management**:
  - `std::thread`, `std::jthread` (auto-joining destructor in C++20).
  - Thread lifecycle, `join()`, `detach()`, thread IDs, `std::this_thread::sleep_for`.
- **Synchronization Primitives**:
  - `std::mutex`, `std::recursive_mutex`, `std::shared_mutex` (Read-Write lock).
  - RAII Guard Wrappers: `std::lock_guard`, `std::unique_lock`, `std::scoped_lock` (deadlock-free multiple locking).
  - Deadlock conditions (Coffman conditions) and prevention strategies.
  - Signaling: `std::condition_variable`, `std::condition_variable_any`, spurious wakeups.
  - Asynchronous Execution: `std::async`, `std::future`, `std::promise`, `std::packaged_task`.
- **C++ Memory Model & Atomics**:
  - `std::atomic<T>`, atomic fetch-and-add, Compare-And-Swap (CAS: `compare_exchange_weak` vs `compare_exchange_strong`).
  - Atomic lock-free check (`is_lock_free()`).
- **Memory Ordering Modes**:
  - `std::memory_order_relaxed`: No synchronization or ordering constraints.
  - `std::memory_order_acquire` & `std::memory_order_release`: Producer-consumer synchronization across threads.
  - `std::memory_order_seq_cst`: Sequentially consistent (default, highest barrier).
  - Compiler vs CPU Instruction Reordering, memory fences/barriers (`std::atomic_thread_fence`).
- **Lock-Free Data Structures**:
  - Single-Producer Single-Consumer (SPSC) Ring Buffer.
  - Multi-Producer Multi-Consumer (MPMC) Bounded Queue.

---

### 🔹 TIER 10: Advanced Architecture, Design Patterns & Interview Mastery
**Objective**: Pass top-tier C++ interviews and architect production-grade software engines.

- **C++ Idioms & Design Patterns**:
  - **Meyers Singleton**: Thread-safe static initialization.
  - **Pimpl Idiom (Pointer to Implementation)**: Compilation firewall, hiding implementation details, speeding up build times.
  - **CRTP (Curiously Recurring Template Pattern)**: Static polymorphism (zero virtual dispatch overhead).
  - **Policy-Based Design**: Customizing template class behaviors at compile time.
  - **RAII Pattern**: Resource management everywhere.
  - Factory, Observer, Strategy, and Builder patterns in modern C++.
- **Performance Profiling & Microbenchmarking**:
  - Microbenchmarking with Google Benchmark.
  - Profiling tools: `perf` (Linux), Valgrind Massif (Heap tracking), Intel VTune.
- **Top Interview Misconceptions & Gotchas**:
  - Exception safety guarantees: Basic, Strong, Nothrow guarantees (`noexcept` qualifier).
  - Static initialization order fiasco across translation units.
  - Dangling references in lambdas and modern views.
  - Undefined Behavior traps (Strict Aliasing, Integer promotion, Sequence points).

---

## 🛠️ Production Capstone Projects

To solidify your mastery, we will build 4 production-grade projects:

1. **Project 1: Ultra-Fast Custom Memory Allocator**
   - High-performance Arena Bump Allocator & Lock-Free Fixed-Size Pool Allocator with alignment support.
2. **Project 2: High-Frequency Lock-Free SPSC/MPMC Ring Buffer Queue**
   - Cache-aligned, lock-free queue using atomic acquire-release semantics for ultra-low latency IPC.
3. **Project 3: Reflection & Custom JSON/Binary Serialization Engine**
   - Powered by C++20 Concepts, Variadic Templates, and Compile-Time Type Inspection.
4. **Project 4: Mini Database Engine / Key-Value Store**
   - Log-Structured Merge-Tree (LSM Tree) with Write-Ahead Logging (WAL) and Memory-Mapped File I/O (`mmap`).

---

> [!TIP]
> **How to study from this folder**:
> 1. We will work through each Tier sequentially.
> 2. Each topic will have its own `.md` concept note file explaining theory, memory diagrams, and edge cases.
> 3. You will write executable `.cpp` code for every single concept to test, break, benchmark, and visualize assembly output.
> 4. Keep this repository synced as your lifelong reference notes!
