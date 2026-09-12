# 🔬 Tier 7: Templates, SFINAE, Metaprogramming & C++20 Concepts

> **Architect's Perspective**: Template Metaprogramming (TMP) shifts computation from runtime to compile-time. Instead of paying CPU cycles during user execution, template metaprograms run inside the compiler parser, generating zero-overhead specialized machine code.

---

## 1. Template Mechanics & Specialization Rules

### Template Instantiation
Templates are code generators (blueprints). The compiler does NOT generate machine code for a template until it is instantiated with concrete type arguments:

```cpp
template <typename T>
T add(T a, T b) { return a + b; }

// Compiler generates two distinct function instances in binary:
add(5, 10);      // Instantiates add<int>(int, int)
add(3.5, 2.5);  // Instantiates add<double>(double, double)
```

---

### Full vs Partial Specialization Rules
* **Full Specialization**: Providing a specific implementation for a concrete set of template parameters. (Allowed for both Class and Function templates!).
* **Partial Specialization**: Providing a specialized implementation for a subset or pattern of types (e.g. specializing for all pointers `T*` or all `std::vector<T>`).

> [!CAUTION]
> **CRITICAL RULE**: Function templates CANNOT be partially specialized in C++! (Only Class templates can be partially specialized). To achieve partial specialization behavior for functions, use Function Overloading, SFINAE, or C++20 Concepts!

```cpp
// Primary Class Template
template <typename T, typename U>
struct Storage { static void print() { std::cout << "Primary Storage\n"; } };

// Partial Specialization (For pointer types)
template <typename T, typename U>
struct Storage<T*, U*> { static void print() { std::cout << "Pointer Partial Specialization\n"; } };

// Full Specialization (For int, double)
template <>
struct Storage<int, double> { static void print() { std::cout << "Full Specialization <int, double>\n"; } };
```

---

## 2. SFINAE (Substitution Failure Is Not An Error)

When substituting template arguments into function signatures during overload resolution, if a substitution results in an invalid type or expression, the compiler does NOT emit an error—it simply **discards that candidate overload from the resolution set**.

### 1. `std::enable_if_t` (SFINAE Workhorse)
```cpp
// Enabled ONLY for integral types
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void process(T val) {
    std::cout << "Processing Integral: " << val << "\n";
}

// Enabled ONLY for floating point types
template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>, typename = void>
void process(T val) {
    std::cout << "Processing Floating Point: " << val << "\n";
}
```

---

### 2. `std::void_t` Detection Idiom
`std::void_t<Ts...>` maps any valid type sequence to `void`. If an expression inside `void_t` is invalid, SFINAE triggers!

```cpp
// Member Detection: Checks if Type T has a member function serialize()
template <typename T, typename = void>
struct has_serialize : std::false_type {};

template <typename T>
struct has_serialize<T, std::void_t<decltype(std::declval<T>().serialize())>> : std::true_type {};
```

---

## 3. C++20 Concepts & Constraints (The Modern Replacement for SFINAE)

C++20 Concepts replace cryptic SFINAE templates with readable, first-class language constraints:

```cpp
// 1. Define a Concept
template <typename T>
concept Printable = requires(T a) {
    std::cout << a; // Requires std::cout << a expression to be valid!
};

template <typename T>
concept Serializable = requires(T a) {
    { a.serialize() } -> std::same_as<std::string>; // Requires serialize() returning std::string
};

// 2. Use Concept to constrain functions cleanly!
template <Printable T>
void printData(const T& data) {
    std::cout << data << "\n";
}
```

### Advantages of Concepts over SFINAE:
1. **Readable Compiler Errors**: Instead of 500 lines of template substitution failure dumps, the compiler outputs: `error: constraints not satisfied: 'T' does not satisfy 'Printable'`.
2. **Faster Compilation**: Concept evaluation is far cheaper for the compiler parser than SFINAE SFINAE-instantiated type traits.

---

## 4. Variadic Templates & Fold Expressions (C++17)

Variadic templates accept an arbitrary number of template arguments using Parameter Packs (`typename... Args`).

### Fold Expression Operators (C++17)
Fold expressions unpack parameter packs directly without needing recursive template calls!

```cpp
// Left Fold Unpacking: (... + args) expands to ((arg1 + arg2) + arg3) ...
template <typename... Args>
auto sumAll(Args... args) {
    return (... + args);
}

// Fold over comma operator to execute print for every argument:
template <typename... Args>
void printAll(Args... args) {
    ( (std::cout << args << " "), ... );
    std::cout << "\n";
}
```

---

## 💡 Key Interview Misconceptions & Traps in Tier 7

1. **Misconception**: SFINAE applies to function bodies.  
   * *Truth*: **FALSE!** SFINAE applies ONLY to the function declaration signature (return types, parameter lists, template default parameters). A syntax error inside the function body `{ ... }` results in a hard compilation failure!

2. **Misconception**: `std::declval<T>()` can be called at runtime.  
   * *Truth*: `std::declval<T>()` returns an rvalue reference of type `T` for use ONLY inside unevaluated contexts like `decltype`, `sizeof`, or `std::void_t`. It has NO function definition and causes a linker error if called at runtime!
