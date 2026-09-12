# 🔬 Tier 6: STL Containers, Hash Tables, Red-Black Trees & C++20 Ranges

> **Architect's Perspective**: Selecting the wrong STL container can degrade performance by orders of magnitude. Understanding container memory layouts, node overheads, and CPU cache locality enables you to pick the exact right data structure for bare-metal performance.

---

## 1. Sequence Containers Internal Architectures

### 1. `std::vector<T>` Mechanics
* **Internal Representation**: Represented by a triple-pointer structure (Size = 24 bytes on 64-bit):
  1. `m_start`: Pointer to the first element in contiguous heap memory.
  2. `m_finish`: Pointer to one past the last initialized element (`size() = m_finish - m_start`).
  3. `m_end_of_storage`: Pointer to the end of allocated capacity (`capacity() = m_end_of_storage - m_start`).

```
std::vector<int> (24 bytes)
+-------------------+
| m_start           | --------> [ 10 | 20 | 30 | 40 | Uninitialized Memory ]
+-------------------+           ^                   ^                    ^
| m_finish          | ------------------------------+                    |
+-------------------+                                                    |
| m_end_of_storage  | ---------------------------------------------------+
+-------------------+
```

* **Growth Factor**: When `size() == capacity()`, calling `push_back()` allocates a new memory block:
  * **GCC / Clang**: 2.0x growth factor.
  * **MSVC**: 1.5x growth factor (prevents memory fragmentation reuse issues).
* **Exception Safety Optimization**: `vector` uses `std::move_if_noexcept`. If `T`'s move constructor is NOT marked `noexcept`, `vector` falls back to **copying** every element during reallocation to guarantee strong exception safety!

---

### 2. `std::deque<T>` (Double-Ended Queue)
* **Internal Representation**: Array of pointers to fixed-size memory blocks (typically 512 bytes per block).
* **Advantage**: Can push/pop at both front and back in $O(1)$ constant time without reallocating existing elements!
* **Tradeoff**: Iterators are complex 32-byte objects (pointer to current, first, last, and node map index), making iteration slightly slower than `std::vector`.

---

### 3. Container Memory & Overhead Comparison Matrix

| Container | Contiguous Memory? | Node Overhead per Element | Random Access Complexity | Primary Use Case |
| :--- | :--- | :--- | :--- | :--- |
| **`std::vector`** | **YES** | **0 bytes** | $O(1)$ | Default choice for 95% of data! |
| **`std::deque`** | Chunked Contiguous | Minimal (Block map) | $O(1)$ | Double-ended queues, large buffers |
| **`std::list`** | NO (Heap scattered) | **16–24 bytes** (Prev & Next pointers) | $O(N)$ | Constant time node splicing |
| **`std::map`** | NO (RB-Tree nodes) | **32–40 bytes** (Parent, Left, Right pointers + Color) | $O(\log N)$ | Sorted key lookups |
| **`std::unordered_map`** | NO (Bucket arrays) | **16–24 bytes** (Next pointer + Hash code) | $O(1)$ Average | Fast key-value lookups |

---

## 2. Hash Tables (`std::unordered_map`) Internals

`std::unordered_map` is implemented using **Separate Chaining**:

```
Bucket Array (std::vector<Node*>)
+------+
| [0]  | ----> [ Node: Key=10, Val="A" ] -> nullptr
+------+
| [1]  | ----> nullptr
+------+
| [2]  | ----> [ Node: Key=42, Val="B" ] -> [ Node: Key=99, Val="C" ] -> nullptr (Collision!)
+------+
```

### Key Performance Metrics:
* **Load Factor**: $\text{Load Factor} = \frac{\text{element count}}{\text{bucket count}}$. Default max load factor is `1.0`.
* **Rehash Overhead**: When load factor exceeds max threshold, `unordered_map` allocates a larger bucket array and re-hashes every existing element!
* **Optimization**: Call `.reserve(N)` upfront to prevent expensive re-hash passes!

---

## 3. C++20 Ranges & Views Pipeline Mechanics

C++20 Ranges transform STL algorithms from verbose nested calls into clean, composable pipelines using the pipe `|` operator:

```cpp
std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// C++20 Range View Pipeline (LAZY EVALUATION: Computes values on-demand during iteration!)
auto results = nums 
             | std::views::filter([](int n) { return n % 2 == 0; })
             | std::views::transform([](int n) { return n * n; });
```

> [!IMPORTANT]
> **Lazy Evaluation Advantage**: `std::views` do NOT create temporary vector copies in memory! They wrap the container in a lightweight view object that evaluates transformations on the fly during range-based `for` loop iterations.

---

## 💡 Key Interview Misconceptions & Traps in Tier 6

1. **Misconception**: `std::vector::erase()` reduces `capacity()`.  
   * *Truth*: `erase()` and `clear()` change `size()`, but **NEVER reduce `capacity()`**! To shrink capacity back to zero, call `vec.shrink_to_fit()` or use the shrink-to-fit swap idiom (`std::vector<T>().swap(vec)`).

2. **Misconception**: `std::map` is faster than `std::vector` for small N search lookups.  
   * *Truth*: Due to CPU L1/L2 cache prefetching, linear search `std::find` on a contiguous `std::vector` is significantly faster than tree-traversal lookup in `std::map` for sizes up to $N \approx 100$! Pointer chasing in tree nodes triggers CPU cache misses.
