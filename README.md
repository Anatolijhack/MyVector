# MyVector — реализация аналога std::vector на C++

## 📌 Описание

`MyVector` — это собственная реализация динамического массива (аналог `std::vector`) с ручным управлением памятью.

Проект демонстрирует глубокое понимание:

* работы с памятью (operator new / delete)
* placement new
* move semantics
* RAII
* шаблонов (templates)

---

## 🚀 Возможности

### 🔹 Базовые операции

* `push_back`, `pop_back`
* `push_front`, `pop_front`
* `insert`, `erase`
* `clear`, `empty`

### 🔹 Работа с памятью

* `reserve` — управление capacity
* автоматическое расширение (capacity * 2)
* перемещение элементов (move вместо copy)

### 🔹 Доступ к элементам

* `operator[]`
* `at`
* `front`, `back`

### 🔹 Итераторы

* `Iterator`
* `ConstIterator`
* поддержка range-based for

### 🔹 Расширенные операции

* `emplace_back`
* `emplace`
* `assign`
* вставка диапазона (`insert(first, last)`)

---

## 🧠 Что реализовано под капотом

* Ручное выделение памяти:

  ```cpp
  operator new(sizeof(T) * capacity);
  ```

* Placement new:

  ```cpp
  new (data + i) T(...)
  ```

* Явный вызов деструкторов:

  ```cpp
  data[i].~T();
  ```

* Move semantics:

  ```cpp
  std::move(data[i])
  ```

---

## ⚠️ Особенности реализации

* Нет allocator (как в std::vector)
* Нет полной exception safety (strong guarantee)
* Нет shrink_to_fit
* Нет bounds checking в operator[]

---

## 📈 Сложность операций

| Операция          | Сложность            |
| ----------------- | -------------------- |
| push_back         | O(1) амортизированно |
| insert            | O(n)                 |
| erase             | O(n)                 |
| reserve           | O(n)                 |
| доступ по индексу | O(1)                 |

---

## 💡 Пример использования

```cpp
MyVector<int> vec;

vec.push_back(10);
vec.push_back(20);
vec.push_front(5);

for (auto& v : vec)
{
    std::cout << v << " ";
}
```

---

## 🧪 Цель проекта

Проект создан для:

* углубления понимания STL
* подготовки к техническим собеседованиям
* демонстрации навыков работы с low-level C++

---

## 🔥 Возможные улучшения

* Exception safety (strong guarantee)
* Поддержка allocator
* shrink_to_fit
* reverse_iterator
* small buffer optimization (SBO)

---

## 👨‍💻 Автор

Разработано как учебный проект для изучения внутренних механизмов STL.

---
