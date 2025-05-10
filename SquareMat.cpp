/**
 * danieldaniel2468@gmail.com
 */

#include "SquareMat.hpp"
using namespace mathlib;

// --- constructors / destructor ---
SquareMat::SquareMat(size_t n)
  : n_(n), data_(nullptr) {
    if (n_ == 0) throw std::invalid_argument("Dimension must be >0");
    data_ = new int[n_ * n_]();
}

SquareMat::SquareMat(const SquareMat& o)
  : n_(o.n_), data_(new int[o.n_ * o.n_]()) {
    for (size_t i = 0; i < n_ * n_; ++i)
        data_[i] = o.data_[i];
}

SquareMat::SquareMat(SquareMat&& o) noexcept
  : n_(o.n_), data_(o.data_) {
    o.n_ = 0;
    o.data_ = nullptr;
}

SquareMat::SquareMat(std::initializer_list<std::initializer_list<int>> init)
  : n_(init.size()), data_(nullptr) {
    if (n_ == 0)
        throw std::invalid_argument("Initializer list cannot be empty");

    // 1) validate all rows before allocation
    for (auto& row : init) {
        if (row.size() != n_)
            throw std::invalid_argument("Non-square init");
    }

    // 2) allocate once validation passed
    data_ = new int[n_ * n_]();

    // 3) fill data
    size_t i = 0;
    for (auto& row : init) {
        size_t j = 0;
        for (int v : row) {
            data_[i * n_ + j++] = v;
        }
        ++i;
    }
}

SquareMat::~SquareMat() {
    delete[] data_;
}

// --- assignment ---
SquareMat& SquareMat::operator=(const SquareMat& o) {
    if (this != &o) {
        delete[] data_;
        n_ = o.n_;
        data_ = new int[n_ * n_]();
        for (size_t i = 0; i < n_ * n_; ++i)
            data_[i] = o.data_[i];
    }
    return *this;
}

SquareMat& SquareMat::operator=(SquareMat&& o) noexcept {
    if (this != &o) {
        delete[] data_;
        n_ = o.n_;
        data_ = o.data_;
        o.n_ = 0;
        o.data_ = nullptr;
    }
    return *this;
}

// --- element access ---
int* SquareMat::operator[](size_t i) {
    if (i >= n_) throw std::out_of_range("Row index out of range");
    return data_ + i * n_;
}

const int* SquareMat::operator[](size_t i) const {
    if (i >= n_) throw std::out_of_range("Row index out of range");
    return data_ + i * n_;
}

#define CHK(o) if (n_ != (o).n_) throw std::invalid_argument("Dimension mismatch")

// --- arithmetic ---
SquareMat SquareMat::operator+(const SquareMat& o) const {
    CHK(o);
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] + o.data_[i];
    return R;
}

SquareMat SquareMat::operator-(const SquareMat& o) const {
    CHK(o);
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] - o.data_[i];
    return R;
}

SquareMat SquareMat::operator*(const SquareMat& o) const {
    CHK(o);
    SquareMat R(n_);
    for (size_t i = 0; i < n_; ++i) {
        for (size_t j = 0; j < n_; ++j) {
            int sum = 0;
            for (size_t k = 0; k < n_; ++k)
                sum += data_[i * n_ + k] * o.data_[k * n_ + j];
            R.data_[i * n_ + j] = sum;
        }
    }
    return R;
}

SquareMat SquareMat::operator*(int s) const {
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] * s;
    return R;
}

SquareMat SquareMat::operator%(const SquareMat& o) const {
    CHK(o);
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] * o.data_[i];
    return R;
}

SquareMat SquareMat::operator%(int m) const {
    if (m == 0) throw std::domain_error("Modulo by zero");
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] % m;
    return R;
}

SquareMat SquareMat::operator/(int s) const {
    if (s == 0) throw std::domain_error("Division by zero");
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = data_[i] / s;
    return R;
}

SquareMat SquareMat::operator^(unsigned p) const {
    SquareMat R(n_);
    for (size_t i = 0; i < n_; ++i)
        R.data_[i * n_ + i] = 1;
    SquareMat B(*this);
    while (p) {
        if (p & 1) R = R * B;
        B = B * B;
        p >>= 1;
    }
    return R;
}

// --- compound assignments ---
SquareMat& SquareMat::operator+=(const SquareMat& o) { return *this = *this + o; }
SquareMat& SquareMat::operator-=(const SquareMat& o) { return *this = *this - o; }
SquareMat& SquareMat::operator*=(const SquareMat& o) { return *this = *this * o; }
SquareMat& SquareMat::operator*=(int s)        { return *this = *this * s; }
SquareMat& SquareMat::operator%=(int m)       { return *this = *this % m; }
SquareMat& SquareMat::operator/=(int s)        { return *this = *this / s; }

// --- unary & special ---
SquareMat SquareMat::operator-() const {
    SquareMat R(n_);
    for (size_t i = 0; i < n_ * n_; ++i)
        R.data_[i] = -data_[i];
    return R;
}

SquareMat& SquareMat::operator++() {
    for (size_t i = 0; i < n_ * n_; ++i) ++data_[i];
    return *this;
}

SquareMat SquareMat::operator++(int) {
    SquareMat tmp(*this);
    ++*this;
    return tmp;
}

SquareMat& SquareMat::operator--() {
    for (size_t i = 0; i < n_ * n_; ++i) --data_[i];
    return *this;
}

SquareMat SquareMat::operator--(int) {
    SquareMat tmp(*this);
    --*this;
    return tmp;
}

SquareMat SquareMat::operator~() const {
    SquareMat R(n_);
    for (size_t i = 0; i < n_; ++i)
        for (size_t j = 0; j < n_; ++j)
            R.data_[j * n_ + i] = data_[i * n_ + j];
    return R;
}

// minor builder for determinant
static void build_minor(const int* src, int* dst, size_t n, size_t skip) {
    size_t idx = 0;
    for (size_t i = 1; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            if (j != skip)
                dst[idx++] = src[i * n + j];
}

int SquareMat::det_recursive(int* buf, size_t k) const {
    if (k == 1) return buf[0];
    if (k == 2) return buf[0] * buf[3] - buf[1] * buf[2];
    int det = 0;
    int* tmp = new int[(k - 1) * (k - 1)];
    for (size_t c = 0; c < k; ++c) {
        build_minor(buf, tmp, k, c);
        int cof = ((c & 1) ? -1 : 1) * buf[c] * det_recursive(tmp, k - 1);
        det += cof;
    }
    delete[] tmp;
    return det;
}

int SquareMat::operator!() const {
    int* tmp = new int[n_ * n_];
    for (size_t i = 0; i < n_ * n_; ++i)
        tmp[i] = data_[i];
    int d = det_recursive(tmp, n_);
    delete[] tmp;
    return d;
}

// comparisons by sum of elements
static int sum_elems(const int* a, size_t len) {
    int s = 0;
    for (size_t i = 0; i < len; ++i) s += a[i];
    return s;
}

bool SquareMat::operator==(const SquareMat& o) const {
    return sum_elems(data_, n_ * n_) == sum_elems(o.data_, n_ * n_);
}
bool SquareMat::operator!=(const SquareMat& o) const { return !(*this == o); }
bool SquareMat::operator<(const SquareMat& o) const { return sum_elems(data_, n_ * n_) < sum_elems(o.data_, n_ * n_); }
bool SquareMat::operator>(const SquareMat& o) const { return o < *this; }
bool SquareMat::operator<=(const SquareMat& o) const { return !(*this > o); }
bool SquareMat::operator>=(const SquareMat& o) const { return !(*this < o); }

namespace mathlib {

std::ostream& operator<<(std::ostream& os, const SquareMat& m) {
    for (size_t i = 0; i < m.n_; ++i) {
        os << "[ ";
        for (size_t j = 0; j < m.n_; ++j) {
            os << m.data_[i * m.n_ + j];
            if (j + 1 < m.n_)
                os << ", ";
            else
                os << " ";
        }
        os << "]\n";
    }
    return os;
}

} // namespace mathlib
