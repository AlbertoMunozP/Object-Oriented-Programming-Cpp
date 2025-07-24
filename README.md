# Object-Oriented Programming in C++ – Virtual Bookstore System

This repository contains a complete academic project designed to implement a **Virtual Bookstore Management System** in modern **C++17**, structured into multiple stages (P0 to P4). Each stage builds on the previous, following an **evolutionary incremental lifecycle model** guided by use cases and object-oriented design principles.

The code is fully tested using automated test suites and compiled with `clang` via `make`. The project demonstrates mastery in C++ through the use of **classes, inheritance, exception safety, templates, STL containers, algorithms, and polymorphism**.

---


##  Practice Breakdown

### Practice 0 (included in `P1/`): Foundational Utility Classes

This stage establishes the core data structures used throughout the project:

- **`Fecha` (Date)**:
  - Multiple constructors for different input formats (e.g., integers, C-strings).
  - Validity checks (day/month/year ranges, leap years).
  - Exception handling via `Fecha::Invalida`.
  - Operators: `+`, `-`, `++`, `--`, `==`, `<`, `<=`, `!=`, etc.
  - Implicit conversion to formatted string.

- **`Cadena` (String)**:
  - Manual memory management using dynamic allocation (`new[]` / `delete[]`).
  - Emulates parts of `std::string`: length, indexing, concatenation.
  - Overloaded operators: assignment, comparison, `+`, `+=`, indexing.
  - Exception safety: invalid access throws `std::out_of_range`.
  - Overloads for `<<` and `>>` to allow I/O streaming.

This stage is crucial to **replace standard types** (e.g., `std::string`) with custom implementations and build a controlled OOP environment.

---

### Practice 1 (included in `P1/`): Stream I/O, Move Semantics & Iterators

Extends `Fecha` and `Cadena` by:

- Adding **stream extraction/insertion operators** (`>>`, `<<`) for both classes.
- Introducing **move semantics**:
  - Move constructor and move assignment in `Cadena`.
- Adding **custom iterators**:
  - Forward and reverse iterators (`begin`, `end`, `rbegin`, `rend`, and const variants), allowing STL-style iteration over characters.

This stage focuses on **stream I/O integration** and alignment with **STL container conventions**.

---

### Practice 2 (in `P4/`): Users, Cards & Shopping Cart – STL Association Maps

Implements use cases 1 and 2 of the system:

- **Classes introduced**:
  - `Usuario`: uniquely identified users, with secure password handling.
  - `Clave`: encrypts and verifies passwords (with custom exceptions).
  - `Numero`: validates and stores credit card numbers.
  - `Tarjeta`: manages credit cards, expiration dates, activation, association with users.
  - `Articulo`: base class for catalog items.

- **Shopping cart management**:
  - `Usuario` holds a `std::unordered_map<Articulo*, unsigned int>` representing the shopping cart.
  - Association with `std::map<Numero, Tarjeta*>` to manage user cards.

- **STL Usage**:
  - `std::map`, `std::unordered_map` for associations.
  - Custom comparators (`OrdenaArticulos`, etc.) for sorting.
  - Exception-safe code.

This stage emphasizes **associative containers and class relationships** (composition and association).

---

### Practice 3 (in `P4/`): Orders & Billing – Bidirectional Associations & STL Algorithms

Implements use case 3:

- **New classes**:
  - `Pedido`: encapsulates a purchase with total cost, date, and associated user/card.
  - `LineaPedido`: holds details of quantity and sale price for each item in a purchase.
  - `Pedido_Articulo` and `Usuario_Pedido`: **association classes** that store bidirectional many-to-many relationships.

- **Key features**:
  - Validations: empty cart (`Pedido::Vacio`), mismatched users (`Pedido::Impostor`), out-of-stock (`Pedido::SinStock`).
  - Output formatting: detailed invoice-like structure using `<<`.
  - Inventory reduction on checkout.

- **STL & Algorithms**:
  - `std::map<Pedido*, ItemsPedido>`, where `ItemsPedido` = `std::map<Articulo*, LineaPedido>`.
  - Usage of `std::remove_if`, `std::find_if` for input validation and sanitization (e.g., card number checks).

This stage highlights **bidirectional associations**, **inter-object coordination**, and **rich object modeling** using STL.

---

### Practice 4 (in `P4/`): Article Hierarchy – Inheritance & Polymorphism

Implements use case 4: article catalog.

- **Hierarchy introduced**:
  - `Articulo` becomes an **abstract base class**.
  - Derived classes:
    - `ArticuloAlmacenable` (abstract): for items with stock.
    - `Libro`: adds page count.
    - `Revista`: adds issue number and periodicity.
    - `LibroDigital`: adds expiration date (not stored).

- **Virtual methods & polymorphism**:
  - Virtual `impresion_especifica()` is overridden in each derived class for type-specific printing.
  - Use of `dynamic_cast` or polymorphic access for formatting.

- **Other additions**:
  - Class `Autor`: stores author info and supports multiple authors per article.
  - `mostrar_carro()`: updated to preserve original output format regardless of polymorphism.

This stage brings full **OOP inheritance and runtime polymorphism**, completing the bookstore model.

---

## Build and Run

Each practice contains a `Makefile` to compile and test the code using `clang++`.

### Prerequisites

- **C++17-compliant compiler** (`clang++`)
- **Make**
- Development tools: `gdb`, `valgrind`, 
- Locale: `es_ES.UTF-8`


