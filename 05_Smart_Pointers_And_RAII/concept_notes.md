# 🔬 Tier 4: Dynamic Memory, RAII, Smart Pointers & Allocators

> **Architect's Perspective**: Dynamic memory allocation in C++ is a powerful privilege. Senior engineers write code where raw `new` and `delete` are completely absent from business logic, fully encapsulated behind RAII (Resource Acquisition Is Initialization) wrappers and smart pointers.

---

## 1. Dynamic Allocation Low-Level Mechanics

### `malloc`/`free` vs `new`/`delete`

| Feature | `malloc` / `free` | `new` / `delete` |
| :--- | :--- | :--- |
| **Origin** | Standard C Library (`<cstdlib>`) | C++ Language Operator |
| **Object Construction** | Allocates raw bytes only; **Constructors are NOT called!** | Allocates bytes AND **executes Constructor** |
| **Object Destruction** | Frees raw bytes; **Destructors are NOT called!** | **Executes Destructor** AND frees bytes |
| **Type Safety** | Returns `void*` (requires manual cast) | Returns typed pointer `T*` |
| **Failure Behavior** | Returns `nullptr` on allocation failure | Throws `std::bad_alloc` exception |
| **Customization** | Cannot be overloaded | Can be globally or locally overloaded (`operator new`) |

---

### `new[]` vs `delete[]` Array Header Trap
When allocating arrays (`int* arr = new int[10];`), the C++ runtime stores a hidden **Array Size Header** (usually 8 bytes immediately preceding the returned array pointer) to record how many destructors must be invoked during `delete[]`.

```
[ Array Length Header (8 bytes) ] [ arr[0] ] [ arr[1] ] ... [ arr[N-1] ]
                                  ^
                                  | Pointer returned by new[]
```

> [!CAUTION]
> **UNDEFINED BEHAVIOR**: Calling single `delete ptr;` on memory allocated with `new T[N]` is Undefined Behavior! It reads wrong header metadata, leading to memory heap corruption or crashing on destructor calls.

---

### Placement `new` Mechanics
Placement `new` constructs an object in a pre-allocated raw memory buffer without allocating new memory:

```cpp
alignas(Hero) char memoryBuffer[sizeof(Hero)]; // Raw stack or arena buffer

// Placement new constructs Hero directly inside memoryBuffer
Hero* heroPtr = new (memoryBuffer) Hero("Thor", 100);

// CRITICAL: Must invoke destructor EXPLICITLY! (delete cannot be called on stack buffer)
heroPtr->~Hero();
```

---

## 2. Smart Pointers Deep-Dive & Memory Layouts

### 1. `std::unique_ptr<T>` (Exclusive Ownership)
* **Semantics**: Single owner. Non-copyable, Move-only!
* **Memory Overhead**: **ZERO overhead**! `sizeof(std::unique_ptr<T>) == sizeof(T*)`.
* **Custom Deleters**: Can accept stateless or stateful custom deletion callables.

```cpp
// Custom Deleter for C-style FILE handles
auto fileDeleter = [](FILE* fp) { if (fp) fclose(fp); };
std::unique_ptr<FILE, decltype(fileDeleter)> filePtr(fopen("data.txt", "r"), fileDeleter);
```

---

### 2. `std::shared_ptr<T>` (Shared Ownership)
* **Semantics**: Multiple owners sharing resource lifetime via reference counting. Destroyed when last `shared_ptr` is destroyed or reset.
* **Internal Memory Layout**: Contains **TWO raw pointers** (Size = 16 bytes on 64-bit):
  1. Pointer to the managed raw object `T*`.
  2. Pointer to the **Control Block**.

```
std::shared_ptr<T>
+---------------------+
| Pointer to Object   | --------------------> [ Managed Object T ]
+---------------------+
| Pointer to CtrlBlk  | -------> +----------------------------------------+
+---------------------+          |          Control Block                 |
                                 +----------------------------------------+
                                 |  Strong Ref Count  (std::atomic<long>) |
                                 |  Weak Ref Count    (std::atomic<long>) |
                                 |  Custom Deleter    (Type erased)       |
                                 |  Custom Allocator  (Type erased)       |
                                 +----------------------------------------+
```

#### Thread Safety Rules of `std::shared_ptr`:
1. **Reference Count Operations**: Increments and decrements of the control block reference count are **ATOMIC** and thread-safe.
2. **Underlying Object Access**: Reading/writing the underlying object `T` from multiple threads is **NOT thread-safe**! Concurrent access requires external mutex locking.

---

### 3. `std::weak_ptr<T>` (Non-Owning Observer)
* **Semantics**: Holds a non-owning reference to a resource managed by `std::shared_ptr`.
* **Purpose**: Solves **Circular Reference Deadlocks** (e.g. Node A -> Node B -> Node A where reference count never drops to zero!).
* **Usage**: Must be converted to `std::shared_ptr` via `.lock()` before accessing underlying object:
  ```cpp
  if (std::shared_ptr<T> lockedPtr = weakRef.lock()) {
      lockedPtr->doSomething(); // Object is still alive!
  } else {
      // Object was already destroyed!
  }
  ```

---

### 4. `std::make_unique` vs `std::make_shared`

```cpp
// Two separate heap allocations (1 for object, 1 for control block):
std::shared_ptr<Widget> sp1(new Widget());

// Single contiguous heap allocation (Object + Control Block combined!):
std::shared_ptr<Widget> sp2 = std::make_shared<Widget>();
```

#### Comparison Matrix:

| Metric | `std::make_shared` | `std::shared_ptr(new T)` |
| :--- | :--- | :--- |
| **Heap Allocations** | **1 Allocation** (Contiguous block) | **2 Allocations** (Separated memory) |
| **Cache Locality** | Excellent (Control block adjacent to object) | Poor (Pointer chasing to control block) |
| **Exception Safety** | Fully safe | Potential leak if secondary expression throws |
| **Memory Deallocation** | Control block & object memory freed ONLY when **both Strong Count AND Weak Count reach 0** | Object memory freed immediately when Strong Count reaches 0 (Weak count keeps only small control block alive) |

---

## 3. Custom Memory Allocation Architecture

High-frequency trading (HFT), game engines, and database kernels avoid general-purpose `malloc`/`new` during critical execution paths due to heap fragmentation and non-deterministic OS mutex latency.

### 1. Arena / Linear Allocator
* **Concept**: Allocates a massive contiguous byte buffer upfront (e.g. 10MB). Memory requests advance a simple "bump pointer".
* **Deallocation**: O(1) bulk reset of the bump pointer to 0.

### 2. Fixed-Size Pool Allocator
* **Concept**: Divides memory into fixed-size slots (e.g. 64-byte slots). Maintains a free-list stack of available slots.
* **Allocation/Deallocation**: Guaranteed $O(1)$ constant time with zero memory fragmentation.

---

## 💡 Key Interview Misconceptions & Traps in Tier 4

1. **Misconception**: `std::shared_ptr` makes object access thread-safe.  
   * *Truth*: Only reference counting is atomic. Concurrent reads/writes to the pointed-to object require explicit mutex protection!

2. **Misconception**: `std::unique_ptr` can be copied if passed as `const std::unique_ptr<T>&`.  
   * *Truth*: Passing by const reference allows observing the smart pointer without transferring ownership, but copying the smart pointer itself (`auto p2 = p1;`) remains strictly forbidden.

3. **Misconception**: `weak_ptr` prevents the memory of an object created with `std::make_shared` from being freed immediately when strong reference count reaches 0.  
   * *Truth*: **TRUE!** Because `make_shared` allocates the object and control block in one single chunk, the raw memory chunk cannot be freed by OS until weak reference count also reaches 0 (though the object's destructor IS invoked immediately when strong count reaches 0).
