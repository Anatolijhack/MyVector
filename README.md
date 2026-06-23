# MyVector — Custom std::vector Implementation in C++

## 📌 Overview

`MyVector` is a custom implementation of a dynamic array similar to `std::vector`, written from scratch to understand how STL containers work internally.

The project focuses on **manual memory management**, **object lifetime control**, and **iterator design**.

---

## ⚙️ Features

### Memory Management

* Raw memory allocation using `operator new`
* Object construction via placement new
* Manual destruction using `~T()`

### Core Functionality

* `push_back`, `push_front`
* `insert`, `erase`
* `insert_period` (range insert)
* `pop_back`, `pop_front`
* `resize`, `reserve`
* `shrink_to_fit`

### Modern C++ Features

* Move semantics (`std::move`)
* Perfect forwarding (`emplace_back`)
* Rule of 5:

  * Copy constructor
  * Move constructor
  * Copy assignment
  * Move assignment
  * Destructor

---

## 🔁 Iterators

Custom iterator implementation with **random access support**:

* `operator++`, `operator--`
* `operator+`, `operator-`
* `operator[]`
* iterator difference
* comparison operators (`<`, `>`, etc.)

👉 Behavior is similar to raw pointers and `std::vector::iterator`

---

## 💡 Key Concepts Learned

* Difference between **memory allocation** and **object construction**
* How **move semantics** improve performance
* Internal mechanics of STL containers
* Importance of **exception safety**
* Why iterators are just abstractions over pointers

---

## ⚠️ Limitations

* No allocator support (unlike `std::vector`)
* Exception safety is not fully guaranteed in all operations
* No SFINAE / advanced template constraints
* Iterator invalidation rules are not strictly enforced
* No optimizations for trivially relocatable types

---

## 🚀 Future Improvements

* Add allocator support (`std::allocator`)
* Implement strong exception guarantee everywhere
* Improve iterator compliance with STL
* Add const-correct API
* Optimize memory operations (`std::uninitialized_move`)

---

## 🧪 Example Usage

```cpp
MyVector<int> v;

v.push_back(1);
v.push_back(2);
v.push_back(3);

auto it = v.begin();
it = it + 1;

v.insert(it, 99);

for (auto x : v)
    std::cout << x << " ";
```

---

## 🏁 Conclusion

This project demonstrates how a vector-like container works internally:

```
vector = raw memory + object lifetime management + element shifting
```

Understanding this removes the "magic" behind STL and gives deeper control over C++ performance and behavior.
