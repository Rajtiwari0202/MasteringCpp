# 🔬 Tier 1: Hardware Memory Layout, Data Primitives, Alignment & Bits

> **Architect's Perspective**: Computer hardware has no understanding of "classes", "objects", or "types". To the CPU, RAM is simply a massive linear array of bytes (0x00 to 0xFF). How your program interprets those bytes—and how efficiently the hardware cache line loads them—determines both correctness and bare-metal performance.

---

## 1. Virtual Address Space Layout

When an operating system launches a 64-bit C++ process, it assigns it a contiguous **Virtual Memory Address Space** (typically 48-bit addressable space = 256 Terabytes on modern x86_64).

```
High Addresses (0x7FFFFFFFFFFF)
+------------------------------------+
|          Kernel Space              | (OS Reserved Memory)
+------------------------------------+
|          Stack Segment             | <--- Grows DOWNWARD (towards low addresses)
|  (Local vars, function stack frames)|
|                 |                  |
|                 v                  |
|                                    |
|                 ^                  |
|                 |                  |
|          Heap Segment              | <--- Grows UPWARD (via brk / sbrk / mmap)
|   (Dynamic malloc / new objects)   |
+------------------------------------+
|          BSS Segment               | (Uninitialized Globals/Statics, Zero-filled)
+------------------------------------+
|          Data Segment              | (Initialized Globals/Statics)
+------------------------------------+
|       Text / Code Segment          | (Read-only CPU Instructions & String Literals)
+------------------------------------+
Low Addresses (0x000000000000)
```

### Segment Breakdown:
1. **Text / Code Segment**: Stores raw binary machine instructions. Marked as **Read-Only** and **Executable** by the OS MMU (Memory Management Unit). Attempts to write here trigger a Segmentation Fault / Access Violation.
2. **Data Segment**: Holds global and static variables initialized with explicit non-zero values (`int g_x = 42;`). Memory is reserved during compilation and loaded directly from binary disk image.
3. **BSS Segment (Block Started by Symbol)**: Holds uninitialized global and static variables (`static int g_y;`). Does NOT take space in the executable file on disk! The OS automatically zeroes this memory range upon process launching.
4. **Heap Segment**: Used for dynamic memory allocations (`new`, `malloc`). Managed by C runtime allocators (e.g. `ptmalloc`, `jemalloc`, `mimalloc`). Grows upward.
5. **Stack Segment**: Stores stack frames (function parameters, local variables, return addresses, saved registers). Extremely fast LIFO allocation (adjusting stack pointer CPU register `rsp`). Grows downward on x86 architectures.

---

## 2. Integer Representation & Overflow Rules

### Two's Complement Mechanics
C++ integers use **Two's Complement** representation for signed values:
* Positive numbers: standard binary notation (e.g. `+5` in 8-bit = `00000101`).
* Negative numbers: Invert all bits and add 1 (e.g. `-5`: Invert `00000101` -> `11111010`, add 1 -> `11111011`).

### Signed vs Unsigned Overflow Rules

> [!CAUTION]
> **CRITICAL C++ RULE**:
> * **Unsigned Integer Overflow** is **DEFINED** by the C++ standard to wrap around using modulo arithmetic ($2^N$). `UINT_MAX + 1` is strictly guaranteed to equal `0`.
> * **Signed Integer Overflow** is **UNDEFINED BEHAVIOR (UB)**. The compiler assumes signed overflow NEVER occurs in valid C++ programs. Compilers aggressively use this assumption to optimize away security bounds checks!

#### UB Optimization Example:
```cpp
// If x is a signed 32-bit int, (x + 1 > x) SHOULD always be true.
// The compiler optimizes 'x + 1 > x' to constant 'true' because signed overflow is UB!
bool check(int x) {
    return x + 1 > x; // Compiler eliminates the check entirely under -O2!
}
```

---

## 3. IEEE 754 Floating-Point Mechanics

Floating-point numbers (`float` [32-bit], `double` [64-bit]) are stored using the **IEEE 754 Standard**:

$$\text{Value} = (-1)^{\text{sign}} \times 2^{\text{exponent} - \text{bias}} \times (1.\text{mantissa})$$

### 32-Bit Single Precision (`float`) Bit Layout:
* **Sign Bit**: 1 bit (0 = positive, 1 = negative).
* **Exponent**: 8 bits (Bias = 127).
* **Mantissa / Significand**: 23 bits (Implicit leading `1.`).

```
 Bit 31     Bits 30..23          Bits 22..0
+-------+------------------+----------------------------------+
| Sign  |     Exponent     |             Mantissa             |
| (1b)  |      (8b)        |              (23b)               |
+-------+------------------+----------------------------------+
```

### Essential Floating-Point Gotchas:
1. **Precision Loss & Representation Errors**: Decimals like `0.1` cannot be exactly represented in binary floating-point ($0.1_{10} = 0.0001100110011..._2$).
   * Never compare floats using `==`! Always use epsilon tolerance: `std::abs(a - b) < 1e-6f`.
2. **Associativity Breakdown**: Floating-point addition is NOT associative!
   * `(1e20f + -1e20f) + 1.0f == 1.0f`
   * `1e20f + (-1e20f + 1.0f) == 0.0f` (1.0 gets completely lost due to mantissa shift truncation!).
3. **Special Values**:
   * `+0.0` and `-0.0` (They compare equal with `==`, but `1.0 / +0.0 = +Inf`, `1.0 / -0.0 = -Inf`).
   * `NaN` (Not a Number): `NaN != NaN` is ALWAYS true! Test with `std::isnan(x)`.

---

## 4. Memory Alignment, Struct Padding & Cache Efficiency

CPUs read memory from RAM into CPU caches in chunks of **Cache Lines** (typically 64 bytes) or natural word sizes (4 bytes for 32-bit, 8 bytes for 64-bit).

### Alignment Requirement
An object of size $S$ is naturally aligned if its virtual memory address is a multiple of $S$.
* `char` (1 byte): can start at any address.
* `short` (2 bytes): address must be divisible by 2.
* `int` / `float` (4 bytes): address must be divisible by 4.
* `double` / `void*` (8 bytes): address must be divisible by 8.

### Structure Padding Traps
If data members are arranged poorly inside a `struct`, the compiler inserts **padding bytes** to enforce alignment rules.

```cpp
// Poorly aligned struct (Size = 24 bytes!)
struct UnalignedData {
    char a;      // 1 byte
    // [3 bytes padding]
    int b;       // 4 bytes
    char c;      // 1 byte
    // [7 bytes padding]
    double d;    // 8 bytes
};

// Optimally aligned struct (Size = 16 bytes!) - Saved 33% memory!
struct AlignedData {
    double d;    // 8 bytes (placed first)
    int b;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // [2 bytes padding]
};
```

### `alignof` and `alignas`
* `alignof(T)`: Queries the alignment requirement of type `T`.
* `alignas(N)`: Forces a variable or struct to align to an $N$-byte memory boundary.

### False Sharing in Multithreaded Code
When two threads on separate CPU cores concurrently modify independent variables that happen to share the same 64-byte cache line, the CPU cache coherence protocol (MESI) repeatedly invalidates the cache line across cores, destroying performance.
* **Fix**: Use `alignas(64)` or `alignas(std::hardware_destructive_interference_size)` to isolate atomic variables on dedicated cache lines!

---

## 💡 Key Interview Misconceptions & Traps in Tier 1

1. **Misconception**: `sizeof(struct)` is simply the sum of `sizeof` its members.  
   * *Truth*: Structure padding bytes inserted for hardware alignment make `sizeof(struct)` equal to or greater than the sum of member sizes, rounded up to a multiple of `alignof(struct)`.

2. **Misconception**: Unsigned integers are safer than signed integers because they can't overflow into negative numbers.  
   * *Truth*: Unsigned wrapping underflow (e.g. `0u - 1u == 4294967295u`) is one of the most common security vulnerabilities in loop bounds checks (`for (unsigned i = 10; i >= 0; i--)` runs infinitely!).

3. **Misconception**: `volatile` makes memory operations thread-safe or atomic.  
   * *Truth*: `volatile` in C++ ONLY tells the compiler not to optimize away reads/writes to memory (used for hardware registers or signal handlers). It provides ZERO thread synchronization, ZERO memory barriers, and ZERO atomicity! Use `std::atomic` for concurrency.
