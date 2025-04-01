#include "utils.hpp"
#include <cmath>

// Could also return an unsigned int as the gcd is always positive
int gcd(int a, int b) {
    // std::abs is used to avoid negative numbers as the gcd is always positive even if the numbers are negative
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int modulo {a % b};
        a = b;
        b = modulo;
    }

    return a;
}
// recursive version
// int gcd(int a, int b) {
//     if (b == 0) {
//         return a;
//     }
//
//     return gcd(b, a % b);
// }
// ternary operator version
// int gcd(unsigned int a, unsigned int b) {
//     return b == 0 ? a : gcd(b, a % b);
// }

Fraction simplify(Fraction const& f) {
    const int divisor {gcd(f.numerator, f.denominator) };

    return {
        f.numerator / divisor,
        f.denominator / divisor
    };
}

// This fonction work on reference instead of return a copy
void simplify_ref(Fraction& f) {
    const int divisor { gcd(f.numerator, f.denominator) };
    f.numerator /= divisor;
    f.denominator /= divisor;
}