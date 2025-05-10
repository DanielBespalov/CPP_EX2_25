/**
 * danieldaniel2468@gmail.com
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"

#include <stdexcept>
#include <sstream>

using namespace mathlib;

TEST_CASE("Constructor validation") {
    CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
    CHECK_THROWS_WITH(SquareMat(0), "Dimension must be >0");

    CHECK_THROWS_AS((SquareMat{{}}), std::invalid_argument);
    CHECK_THROWS_WITH((SquareMat{{}}), "Non-square init");

    CHECK_THROWS_AS((SquareMat{{1,2},{3}}), std::invalid_argument);
    CHECK_THROWS_WITH((SquareMat{{1,2},{3}}), "Non-square init");
}

TEST_CASE("Element access and out-of-range") {
    SquareMat m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    CHECK(m[0][0] == 1);
    CHECK(m[1][1] == 4);

    CHECK_THROWS_AS((void)m[2], std::out_of_range);
    CHECK_THROWS_WITH((void)m[2], "Row index out of range");
}

TEST_CASE("Arithmetic operations and dimension mismatch") {
    SquareMat A{{1,2},{3,4}};
    SquareMat B{{5,6},{7,8}};

    auto C = A + B;
    CHECK(C[0][0] == 6);

    auto D = B - A;
    CHECK(D[1][1] == 4);

    auto M = A * B;
    CHECK(M[0][0] == 1*5 + 2*7);

    CHECK((A * 2)[1][0] == 6);
    CHECK((2 * A)[0][1] == 4);

    SquareMat C3(3);
    CHECK_THROWS_AS(A + C3, std::invalid_argument);
    CHECK_THROWS_WITH(A + C3, "Dimension mismatch");
}

TEST_CASE("Element-wise mod/div and error messages") {
    SquareMat B{{1,2},{3,4}};

    CHECK_THROWS_AS(B % 0, std::domain_error);
    CHECK_THROWS_WITH(B % 0, "Modulo by zero");

    CHECK_THROWS_AS(B / 0, std::domain_error);
    CHECK_THROWS_WITH(B / 0, "Division by zero");

    auto Z = B % 3;
    CHECK(Z[0][1] == 2);
}

TEST_CASE("Determinant and transpose") {
    SquareMat M{{1,2},{3,4}};
    CHECK(!M == -2);

    auto T = ~M;
    CHECK(T[0][1] == 3);
    CHECK(T[1][0] == 2);
}

TEST_CASE("Increment and decrement") {
    SquareMat C{{1,1},{1,1}};
    ++C;  CHECK(C[0][0] == 2);
    C++;  CHECK(C[0][0] == 3);
    --C;  CHECK(C[0][0] == 2);
    C--;  CHECK(C[0][0] == 1);
}

TEST_CASE("Power operator") {
    SquareMat P{{1,1},{1,0}};
    auto P5 = P ^ 5;
    CHECK(P5[0][0] == 8);
    CHECK(P5[0][1] == 5);
}

TEST_CASE("Comparisons and compound assigns") {
    SquareMat A{{1,1},{1,1}};
    SquareMat B{{2,2},{2,2}};
    CHECK(A < B);
    CHECK(B > A);
    CHECK(A <= B);
    CHECK(B >= A);
    CHECK(A == A);
    CHECK(A != B);

    A += B; CHECK(A[0][0] == 3);
    A -= B; CHECK(A[0][0] == 1);
    A *= B; CHECK(A[0][0] == 1*2 + 1*2);
    A *= 2; CHECK(A[0][0] == 8);
    A /= 2; CHECK(A[0][0] == 4);
    A %= 2; CHECK(A[0][0] == 0);
}

TEST_CASE("Element-wise multiply container") {
    SquareMat X{{1,2},{3,4}};
    SquareMat Y{{5,6},{7,8}};
    auto W = X % Y;
    CHECK(W[0][1] == 12);
    CHECK(W[1][0] == 21);
}

TEST_CASE("Unary negation and zero-power identity") {
    SquareMat A{{2,-3},{4,5}};
    auto N = -A;
    CHECK(N[0][0] == -2);
    CHECK(N[0][1] ==  3);

    auto Z = A ^ 0;
    CHECK(Z[0][0] == 1);
    CHECK(Z[0][1] == 0);
    CHECK(Z[1][0] == 0);
    CHECK(Z[1][1] == 1);
}

TEST_CASE("Scalar division and modulo results") {
    SquareMat M{{10,15},{7,-3}};
    auto D = M / 5;
    CHECK(D[0][0] == 2);
    CHECK(D[0][1] == 3);

    auto R = M % 4;
    CHECK(R[0][0] == 2);
    CHECK(R[1][1] == -3);
}

TEST_CASE("Copy assignment deep copy") {
    SquareMat A{{7,8},{9,10}};
    SquareMat B(2);
    B = A;
    A[1][1] = 99;
    CHECK(B[1][1] == 10);
}

TEST_CASE("3x3 matrix operations and determinant") {
    SquareMat M1{{1,2,3},{4,5,6},{7,8,9}};
    SquareMat M2{{9,8,7},{6,5,4},{3,2,1}};
    auto S = M1 + M2;
    CHECK(S[0][0] == 10);
    auto P2 = M1 * M2;
    CHECK(P2[2][2] == 90);
    CHECK(!M1 == 0);
}

TEST_CASE("Inequality of different matrices") {
    SquareMat A{{1,0},{0,1}};
    SquareMat B{{0,1},{1,0}};
    CHECK(A == B);
    CHECK(!(A != B));
}

TEST_CASE("Self-assignment safety") {
    SquareMat A{{1,2},{3,4}};
    A = A; CHECK(A[0][0] == 1);
    A = std::move(A); CHECK(A[1][1] == 4);
}

TEST_CASE("Move constructor and move assignment") {
    SquareMat A{{5,6},{7,8}};
    SquareMat M(std::move(A));
    CHECK(M[0][0] == 5);
    CHECK(M[1][1] == 8);
    SquareMat B{{1,1},{1,1}};
    B = std::move(M);
    CHECK(B[0][1] == 6);
}

TEST_CASE("3x3 transpose and determinant of non-singular") {
    SquareMat M{{2,0,1},{1,3,4},{5,6,7}};
    auto T3 = ~M;
    CHECK(T3[0][2] == 5);
    CHECK(T3[2][0] == 1);
    CHECK(!M == -15);
}

TEST_CASE("Power operator p=1 and chaining") {
    SquareMat A2{{2,3},{4,5}};
    auto P1 = A2 ^ 1;
    CHECK(P1[0][0] == 2);
    CHECK(P1[1][1] == 5);
    auto Cc = ((A2 + P1) * P1) - A2;
    CHECK(Cc[0][0] == 30);
}

TEST_CASE("Sum-based comparisons with equal sums but different matrices") {
    SquareMat A3{{1,1},{1,1}};
    SquareMat B3{{2,2},{0,0}};
    CHECK(A3 == B3);
    CHECK(!(A3 != B3));
}

TEST_CASE("1x1 matrix operations") {
    SquareMat S(1);
    S[0][0] = -3;
    CHECK(S[0][0] == -3);
    CHECK(!S == -3);
    auto P = S ^ 3;
    CHECK(P[0][0] == -27);
    auto M3 = S * 5;
    CHECK(M3[0][0] == -15);
    auto R3 = S % 4;
    CHECK(R3[0][0] == (-3 % 4));
    auto D3 = S / -1;
    CHECK(D3[0][0] == 3);
    auto T3 = ~S;
    CHECK(T3[0][0] == -3);
}

TEST_CASE("Compound chain operations") {
    SquareMat Z{{1,2},{3,4}};
    SquareMat W = Z;
    W += Z;
    W *= 2;
    CHECK(W[0][0] == 4);
    CHECK(W[1][1] == 16);
}

TEST_CASE("Exponentiation associativity") {
    SquareMat M4{{1,2},{3,4}};
    auto A_a = (M4 ^ 2) ^ 3;
    auto B_b = M4 ^ 6;
    CHECK(A_a == B_b);
}

TEST_CASE("Complex chaining operations") {
    SquareMat A5{{1,2},{3,4}};
    SquareMat B5{{5,6},{7,8}};
    auto R5 = (A5 + B5) * (~A5);
    R5 = R5 ^ 2;
    CHECK(R5[0][0] == 2184);
}

TEST_CASE("Arithmetic * and % dimension mismatch for matrices") {
    SquareMat A6(2);
    SquareMat B6(3);
    CHECK_THROWS_AS(A6 * B6, std::invalid_argument);
    CHECK_THROWS_WITH(A6 * B6, "Dimension mismatch");
    CHECK_THROWS_AS(A6 % B6, std::invalid_argument);
    CHECK_THROWS_WITH(A6 % B6, "Dimension mismatch");
}

TEST_CASE("Compound assignment dimension mismatch") {
    SquareMat A7(2);
    SquareMat B7(3);
    CHECK_THROWS_AS((A7 *= B7), std::invalid_argument);
    CHECK_THROWS_WITH((A7 *= B7), "Dimension mismatch");
}

TEST_CASE("Scalar division rounding towards zero for negatives") {
    SquareMat M8{{3,-3},{5,-5}};
    auto D8 = M8 / 2;
    CHECK(D8[0][0] == 1);
    CHECK(D8[0][1] == -1);
    CHECK(D8[1][0] == 2);
    CHECK(D8[1][1] == -2);
}

TEST_CASE("Modulo with negative modulus") {
    SquareMat M9(1);
    M9[0][0] = 3;
    auto R9 = M9 % -2;
    CHECK(R9[0][0] == 1);
}

TEST_CASE("Division by one returns same matrix") {
    SquareMat M10{{7,8},{9,10}};
    auto D10 = M10 / 1;
    CHECK(D10 == M10);
}
