# C++ System Programming & Modern Language Reference

A comprehensive technical repository for mastering low-level system programming, hardware-level memory models, template metaprogramming, modern C++ specifications (C++11 through C++23), lock-free concurrency, design patterns, and technical interview edge cases.

---

## 🛠️ Repository Navigation

The codebase is organized into twelve sequential modules, followed by production-grade capstone projects and legacy practice code. Each module contains an authoritative theoretical guide (`concept_notes.md`) alongside verified, executable C++ code demonstrations (`01_..._demo.cpp`).

| Module | Topic | Core Focus | Notes & Demos |
| :--- | :--- | :--- | :--- |
| **01** | **Compilation & Toolchains** | Preprocessing, Compilation (AST/IR), Linker, Name Mangling, `extern "C"`, Sanitizers | [Notes](./01_Compilation_Toolchains_Assembly/concept_notes.md) |
| **02** | **Memory Layout & Primitives** | Virtual Memory Segments, Struct Padding, IEEE 754 Floats, `alignof`/`alignas` | [Notes](./02_Memory_Layout_And_Primitives/concept_notes.md) |
| **03** | **Pointers & Value Categories** | Pointer Arithmetic, Lvalues, PRvalues, Xvalues, Reference Collapsing Rules | [Notes](./03_Pointers_References_Value_Categories/concept_notes.md) |
| **04** | **OOP & Vtable Layout** | Vtable/Vptr Mechanics, Multiple Inheritance Offsets, Object Slicing, Rule of 0/3/5 | [Notes](./04_OOP_Vtables_And_Memory_Layout/concept_notes.md) |
| **05** | **Smart Pointers & RAII** | Placement `new`, `unique_ptr`, `shared_ptr` Control Blocks, `weak_ptr` Deadlock Fixes | [Notes](./05_Smart_Pointers_And_RAII/concept_notes.md) |
| **06** | **Modern C++ (11–23)** | Move Semantics, `std::forward`, Lambdas, `consteval`, `variant`/`visit`, `string_view`/`span` | [Notes](./06_Modern_Cpp_11_to_23/concept_notes.md) |
| **07** | **STL Deep Dive & Iterators** | Vector Capacity Growth, Hash Table Load Factors, Iterators, C++20 Lazy Ranges | [Notes](./07_STL_Deep_Dive_And_Iterators/concept_notes.md) |
| **08** | **Templates & Metaprogramming** | Template Specialization, SFINAE (`void_t`), C++20 Concepts/Constraints, Fold Expressions | [Notes](./08_Templates_And_Metaprogramming/concept_notes.md) |
| **09** | **OS Systems & Hardware** | Page Tables, Cache Hierarchy, False Sharing Isolation, Data-Oriented Design (SoA vs AoS) | [Notes](./09_Systems_OS_And_Hardware/concept_notes.md) |
| **10** | **Concurrency & Lock-Free** | Mutexes, `std::scoped_lock`, Acquire-Release Semantics, Lock-Free SPSC Ring Buffer | [Notes](./10_Concurrency_And_LockFree/concept_notes.md) |
| **11** | **Design Patterns & Architecture** | Meyers Thread-Safe Singleton, CRTP Static Polymorphism, Policy-Based Design | [Notes](./11_Design_Patterns_And_Architecture/concept_notes.md) |
| **12** | **Interview Traps & UB Catalog** | Undefined Behavior Catalog, Copy-and-Swap Exception Safety, `std::bit_cast` | [Notes](./12_Interview_Traps_And_Misconceptions/concept_notes.md) |

---

## 🏗️ Capstone Projects

Located under [`Capstone_Projects/`](./Capstone_Projects/):

1. **[Project 1: High-Performance Custom Memory Allocator](./Capstone_Projects/Project1_Custom_Allocator/)**
   - Implements an `ArenaBumpAllocator` providing $O(1)$ linear allocation and $O(1)$ bulk resets.
   - Implements a `FixedPoolAllocator` providing $O(1)$ block allocation and free-list recycling with zero heap fragmentation.

---

## 📂 Legacy Practice Vault

Located under [`00_Legacy_Practice/`](./00_Legacy_Practice/):
Contains preliminary algorithm practice scripts, data structure implementations, and problem-solving exercises.

---

## 💻 Build and Compilation Guide

All code demonstrations are written according to the **C++20 ISO Standard**.

### Compiler Prerequisites
- **GCC**: 10.0+ (MinGW-w64 on Windows)
- **Clang**: 11.0+
- **MSVC**: Visual Studio 2019 16.10+

### Recommended Compilation Commands

#### General Compilation (Standard Debug):
```bash
g++ -Wall -Wextra -Wpedantic -std=c++20 path/to/demo.cpp -o demo.exe
```

#### Production Optimization Build:
```bash
g++ -O3 -DNDEBUG -std=c++20 path/to/demo.cpp -o demo.exe
```

#### Sanitizer Diagnostic Build (ASan & UBSan):
```bash
g++ -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -std=c++20 path/to/demo.cpp -o demo.exe
```

---

## 📜 Curriculum Blueprint & Study Tracker

- **[00_Curriculum_And_Roadmap.md](./00_Curriculum_And_Roadmap.md)** — Exhaustive syllabus detailing assembly instructions, memory diagrams, and core concepts.
- **[NOTION_STUDY_TRACKER.md](./NOTION_STUDY_TRACKER.md)** — Interactive Notion-ready study blueprint and progress log.
