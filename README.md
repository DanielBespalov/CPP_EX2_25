# SquareMat Library

A simple C++ library for square matrices of integers, implemented without using any STL containers (only raw arrays).

## Features

- **Dynamic square matrices** of any dimension `n ≥ 1`.  
- **Constructors**  
  - `SquareMat(size_t n)` — creates an `n × n` zero matrix.  
  - `SquareMat(std::initializer_list<std::initializer_list<int>> init)` — initializer-list construction (throws on empty or non-square init).  
  - Copy and move constructors supported.  
- **Element access** via `operator[]` with bounds checking.  
- **Arithmetic operators**  
  - `+`, `-` (element-wise add/sub).  
  - `*` (matrix multiply) and scalar multiply.  
  - `%` (element-wise multiply) and element-wise `%` and `/` with scalars.  
  - `^` exponentiation (power by squaring).  
- **Compound assignments**: `+=`, `-=`, `*=`, `%=` , `/=`.  
- **Unary ops**: negation `-`, prefix/postfix `++`/`--`, transpose `~`, determinant `!`.  
- **Comparisons**  
  - `==`, `!=` (element-wise equality).  
  - `<, >, <=, >=` compare by sum of all elements.  
- **Output**: stream `operator<<` prints row-by-row.  
- **Error handling**: throws `std::invalid_argument`, `std::out_of_range`, `std::domain_error` for invalid inputs.  
- **No STL containers**: all storage is via `new[]`/`delete[]`.

## Requirements

- C++17 (or later)  
- `g++` or compatible compiler  
- [Doctest](https://github.com/onqtam/doctest) `doctest.h` placed in project root 
- `valgrind` (for memory leak checks)

## Build & Run

1. **Build demo**
   make Main
   
3. **Run unit tests**
   make test
   
4. **Memory leak check**
   make valgrind

5. **Clean**
   make clean
   צ

