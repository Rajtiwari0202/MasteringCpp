# 🔬 Tier 3: OOP, Virtual Tables (Vtables), Multiple Inheritance & Object Memory Layout

> **Architect's Perspective**: Dynamic polymorphism in C++ is zero-magic. It is executed via explicit memory offsets, compiler-injected pointers (`vptr`), and function pointer tables (`vtable`). Understanding object memory layout allows you to optimize virtual dispatch costs, prevent object slicing, and write exception-safe resource managers.

---

## 1. Object Memory Layout & Vtable Mechanics

When a class declares at least one `virtual` function (or inherits from one), the compiler automatically injects a hidden pointer called **`vptr` (Virtual Pointer)** into the object's memory layout.

```
       +-------------------------------+
       |       Derived Object          |
       +-------------------------------+
0x0000 |  vptr (Virtual Pointer)       | ------->  +-------------------------------+
       +-------------------------------+           |      Derived Class Vtable     |
0x0008 |  int m_baseData (4 bytes)     |           +-------------------------------+
0x000C |  [4 bytes padding]            |   0x0000  | &Derived::virtualFunc1        |
       +-------------------------------+           +-------------------------------+
0x0010 |  double m_derivedData (8b)    |   0x0008  | &Derived::virtualFunc2        |
       +-------------------------------+           +-------------------------------+
```

### Vtable & Vptr Execution Steps:
1. **Instantiation**: During constructor execution, the compiler sets the object's `vptr` to point to the static `vtable` array belonging to that specific class.
2. **Virtual Call Execution**: When calling `basePtr->virtualFunc()`:
   * Fetch `vptr` from object address (`*basePtr`).
   * Look up function pointer at index slot $K$ inside `vtable` (`vtable[K]`).
   * Dereference and jump CPU execution to that function address (`call rax`).

### Performance Cost of Virtual Dispatch:
* **Memory Cost**: Every object instance incurs an extra pointer size (8 bytes on 64-bit systems) for `vptr`.
* **Indirection Overhead**: Indirect branch call (`call [rax]`) prevents CPU instruction pipelining and branch prediction.
* **Inlining Invalidation**: Virtual calls generally cannot be inlined, missing compiler optimization opportunities.
* *Architect Note*: Mark functions `final` or classes `final` to enable **Compiler Devirtualization**!

---

## 2. Inheritance Memory Layouts

### Single Inheritance Layout
Base member variables appear first in memory, followed immediately by Derived member variables.

### Multiple Inheritance Layout
When a class inherits from multiple base classes (`class Derived : public Base1, public Base2`), the object contains **MULTIPLE `vptr` pointers**!

```
+------------------------------------+
|  Base1 Subobject                   |
|  - Base1 vptr1                      | -----> Points to Base1-in-Derived Vtable
|  - Base1 member data               |
+------------------------------------+
|  Base2 Subobject                   |
|  - Base2 vptr2                      | -----> Points to Base2-in-Derived Vtable
|  - Base2 member data               |
+------------------------------------+
|  Derived Member Data               |
+------------------------------------+
```

> [!WARNING]
> **Pointer Casting Offset Shift**:
> Casting a `Derived*` to `Base2*` actually **alters the numerical pointer address in memory** by adding the offset of `Base2` within `Derived`!
> ```cpp
> Derived* d = new Derived();
> Base1* b1 = d; // Address b1 == d
> Base2* b2 = d; // Address b2 == d + sizeof(Base1) (Offset shift!)
> ```

---

## 3. Diamond Inheritance & Virtual Base Classes

The **Diamond Problem** occurs when two derived classes inherit from a common base class, and a bottom class inherits from both:

```
        +---------+
        |  Animal |
        +---------+
         /       \
        /         \
  +------+       +------+
  | Mammal|      |Bird  |
  +------+       +------+
        \         /
         \       /
      +-------------+
      |   Bat       |
      +-------------+
```

Without `virtual` inheritance, `Bat` contains **TWO separate instances** of `Animal`, creating ambiguity (`bat.eat()` fails!).

### Fix: Virtual Base Class (`class Mammal : public virtual Animal`)
By declaring base classes `virtual`, the compiler ensures only **ONE shared instance** of `Animal` exists inside `Bat`.
* **Memory Cost**: Increases object size due to injecting a **Virtual Base Pointer (`vbase_offset`)** table to dynamically calculate the memory displacement of `Animal` at runtime.

---

## 4. The Rule of 0 / 3 / 5 & Object Lifetime Rules

Resource management classes must maintain strict ownership rules over their encapsulated memory/handles:

```cpp
class ResourceOwner {
public:
    // 1. Destructor
    ~ResourceOwner();

    // 2. Copy Constructor
    ResourceOwner(const ResourceOwner& other);

    // 3. Copy Assignment Operator
    ResourceOwner& operator=(const ResourceOwner& other);

    // 4. Move Constructor
    ResourceOwner(ResourceOwner&& other) noexcept;

    // 5. Move Assignment Operator
    ResourceOwner& operator=(ResourceOwner&& other) noexcept;
};
```

### The Rule Rules:
* **Rule of 0**: If your class does not manually manage raw memory/handles, do NOT define any of the 5 special member functions! Use RAII types (`std::vector`, `std::string`, `std::unique_ptr`).
* **Rule of 3**: If you define a custom destructor, copy constructor, or copy assignment, you MUST define all 3 to avoid double-free bugs or memory leaks!
* **Rule of 5**: In C++11 and beyond, declaring a custom copy operation disables automatic generation of move operations. Define or `= default` all 5 functions!

---

## 5. Object Slicing Trap

Object Slicing occurs when a Derived object is assigned or passed by value to a Base object variable:

```cpp
Derived derivedObj;
Base baseObj = derivedObj; // SLICED!
```

* **What happens under the hood**: The compiler invokes `Base::copy_constructor`, copying ONLY the base subobject portion of `derivedObj`. The derived member variables and derived `vptr` are **completely stripped ("sliced") away**!
* **Prevention**: Always pass polymorphic objects by **Reference (`Base&`)** or **Smart Pointer (`std::unique_ptr<Base>`)**!

---

## 💡 Key Interview Misconceptions & Traps in Tier 3

1. **Misconception**: Destructors in base classes don't need to be `virtual`.  
   * *Truth*: Deleting a derived object through a pointer to a base class (`Base* ptr = new Derived(); delete ptr;`) when the Base destructor is non-virtual results in **UNDEFINED BEHAVIOR**! Only `Base::~Base()` executes, leaking all derived resources!

2. **Misconception**: Virtual functions cannot be called inside constructors/destructors.  
   * *Truth*: You CAN call them, but **virtual dispatch is DISABLED inside constructors and destructors**! When `Base` constructor executes, the object's `vptr` points to `Base` vtable (because `Derived` members haven't been constructed yet!). The call resolves to `Base::func()`, NOT `Derived::func()`.

3. **Misconception**: `override` is mandatory for virtual function overrides.  
   * *Truth*: `override` is syntactically optional in legacy code, BUT it is a vital modern compiler check. If signature types mismatch slightly without `override`, you silently create a new function instead of overriding the base method!
