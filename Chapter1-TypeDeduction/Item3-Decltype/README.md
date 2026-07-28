# Item 3: `decltype` — and a C++23 surprise (P2266)

This example explores how `decltype` and `decltype(auto)` deduce types for a
returned local variable, and documents a **breaking change introduced in C++23**
by [P2266 "Simpler implicit move"](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2266r3.html).

## The code

[`decltype.cpp`](decltype.cpp):

```cpp
decltype(auto) f1() { int x = 0; return x;   } // bare id-expression
decltype(auto) f2() { int x = 0; return (x); } // parenthesized id-expression

int main() {
    decltype(auto) c  = f1();
    decltype(auto) c2 = f2();
    SHOW(c);
    SHOW(c2);
}
```

Types are printed at runtime with a helper that prints `__PRETTY_FUNCTION__`
(GCC/Clang; use `__FUNCSIG__` on MSVC). Unlike `typeid`, this preserves
references and cv-qualifiers:

```cpp
template<typename T>
void printType(const char* name) {
    cout << name << " has type: " << __PRETTY_FUNCTION__ << "\n";
}
#define SHOW(x) printType<decltype(x)>(#x)
```

## The finding

The deduced return type of `f2` — and therefore the type of `c2` — **depends on
the C++ standard version**:

| Expression        | ≤ C++20 | C++23   | Why |
|-------------------|---------|---------|-----|
| `f1` → `return x;`   | `int`   | `int`   | Bare id-expression: `decltype` always yields the *declared* type, ignoring value category. |
| `f2` → `return (x);` | `int&`  | `int&&` | Parenthesized id-expression: `decltype` uses value category. See below. |

### Why `f2` changed

`f2`'s return type is `decltype((x))` applied to the return expression, so the
**value category** of `(x)` decides the result:

- **≤ C++20:** `(x)` is an **lvalue** of type `int` → `decltype` → `int&`
- **C++23:** under P2266, `(x)` is a *move-eligible* expression (a possibly
  parenthesized id-expression naming a local variable in a `return`) and is now
  treated as an **xvalue** → `decltype` → `int&&`

Only the **parenthesized** form is affected. `f1`'s bare `return x;` stays `int`
in every standard, because for an unparenthesized id-expression `decltype` yields
the declared type and ignores value category.

## Reproducing

```bash
for std in c++14 c++17 c++20 c++23; do
  echo "=== -std=$std ==="
  g++ -std=$std decltype.cpp -o /tmp/decltype && /tmp/decltype
done
```

Output (GCC 13.3.0):

```
=== -std=c++14 ===
c has type: void printType(const char*) [with T = int]
c2 has type: void printType(const char*) [with T = int&]
=== -std=c++17 ===
c has type: void printType(const char*) [with T = int]
c2 has type: void printType(const char*) [with T = int&]
=== -std=c++20 ===
c has type: void printType(const char*) [with T = int]
c2 has type: void printType(const char*) [with T = int&]
=== -std=c++23 ===
c has type: void printType(const char*) [with T = int]
c2 has type: void printType(const char*) [with T = int&&]
```

## ⚠️ This code has undefined behavior

Regardless of standard, `f2` returns a reference (`int&` or `int&&`) to the local
variable `x`, which is destroyed when `f2` returns. **Inspecting `c2`'s type is
fine, but reading its value is undefined behavior.** GCC warns:

```
decltype.cpp:17:9: warning: reference to local variable 'x' returned [-Wreturn-local-addr]
```

## Takeaway

This is a well-known example of P2266 being a breaking change: Scott Meyers'
*Effective Modern C++* Item 3 uses exactly `return (x);` to demonstrate that
`decltype((x))` is `int&`. That is accurate for C++14 through C++20, but C++23
silently turns it into `int&&`. If you rely on the deduced type of a
parenthesized returned local, check your `-std` setting.
