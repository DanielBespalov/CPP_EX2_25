/**
 * danieldaniel2468@gmail.com
 */

#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <iostream>
#include <stdexcept>
#include <initializer_list>

namespace mathlib {

// SquareMat: simple n×n integer matrix using raw arrays (no STL containers)
class SquareMat {
private:
    size_t n_;    // dimension
    int*   data_; // row-major storage (size n_*n_)

    // helper: compute determinant recursively on a buffer of size k×k
    int det_recursive(int* buf, size_t k) const;

public:
    // --- constructors / destructor ---
    explicit SquareMat(size_t n);                              // zero-init, n>0
    SquareMat(const SquareMat& o);                             // copy
    SquareMat(SquareMat&& o) noexcept;                         // move
    SquareMat(std::initializer_list<std::initializer_list<int>> init); // init list, non-empty
    ~SquareMat();                                              // cleanup

    // --- assignment ---
    SquareMat& operator=(const SquareMat& o);                  // copy-assign
    SquareMat& operator=(SquareMat&& o) noexcept;              // move-assign

    // --- element access ---
    int*       operator[](size_t i);                           // row i (writable)
    const int* operator[](size_t i) const;                     // row i (read-only)

    // --- arithmetic ---
    SquareMat operator+(const SquareMat& o) const;             // element-wise add
    SquareMat operator-(const SquareMat& o) const;             // element-wise sub
    SquareMat operator*(const SquareMat& o) const;             // matrix multiply
    SquareMat operator*(int s) const;                          // scalar multiply
    friend SquareMat operator*(int s, const SquareMat& m) {    // commutative scalar
        return m * s;
    }
    SquareMat operator%(const SquareMat& o) const;             // element-wise multiply
    SquareMat operator%(int m) const;                          // element-wise mod
    SquareMat operator/(int s) const;                          // element-wise div
    SquareMat operator^(unsigned p) const;                     // power by squaring

    // --- compound assignments ---
    SquareMat& operator+=(const SquareMat& o);
    SquareMat& operator-=(const SquareMat& o);
    SquareMat& operator*=(const SquareMat& o);
    SquareMat& operator*=(int s);
    SquareMat& operator%=(int m);
    SquareMat& operator/=(int s);

    // --- unary / special ---
    SquareMat operator-() const;                               // negation
    SquareMat& operator++();                                   // prefix ++
    SquareMat  operator++(int);                                // postfix ++
    SquareMat& operator--();                                   // prefix --
    SquareMat  operator--(int);                                // postfix --
    SquareMat  operator~() const;                              // transpose
    int         operator!() const;                             // determinant

    // --- comparisons (by sum of all elements) ---
    bool operator==(const SquareMat& o) const;
    bool operator!=(const SquareMat& o) const;
    bool operator< (const SquareMat& o) const;
    bool operator> (const SquareMat& o) const;
    bool operator<=(const SquareMat& o) const;
    bool operator>=(const SquareMat& o) const;

    // --- output ---
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& m);
};

} // namespace mathlib

#endif // SQUAREMAT_HPP