/**
 * danieldaniel2468@gmail.com
 */

#include <iostream>
#include "SquareMat.hpp"

using mathlib::SquareMat;

int main() {
    try {
        // Demo 3x3 matrices
        SquareMat A{{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}};
        SquareMat B{{9, 8, 7},
                   {6, 5, 4},
                   {3, 2, 1}};

        std::cout << "Matrix A:\n" << A;
        std::cout << "Matrix B:\n" << B;

        std::cout << "A + B =\n" << (A + B);
        std::cout << "A - B =\n" << (A - B);
        std::cout << "A * B =\n" << (A * B);

        std::cout << "Element-wise A % B =\n" << (A % B);
        std::cout << "A * 3 =\n" << (A * 3);
        std::cout << "3 * B =\n" << (3 * B);
        std::cout << "A / 2 =\n" << (A / 2);
        std::cout << "B % 4 =\n" << (B % 4);

        std::cout << "-A =\n" << (-A);
        std::cout << "+ +A =\n"; ++A; std::cout << A;
        std::cout << "--B =\n"; --B; std::cout << B;

        std::cout << "Transpose of A: \n" << ~A;
        std::cout << "Determinant of original A: " << !(A ^ 0) << " (should be 1 for identity when power=0)\n";
        std::cout << "Determinant of B: " << !B << "\n";

        // Power
        SquareMat P{{1,1}, {1,0}};
        std::cout << "Fibonacci power P^5 =\n" << (P ^ 5);

        // Comparisons
        std::cout << std::boolalpha;
        std::cout << "A == B? " << (A == B) << '\n';
        std::cout << "A < B?  " << (A < B)  << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
