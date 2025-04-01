#include "fraction.hpp"
#include "utils.hpp"

#include <iostream>

void Fraction::display() {
    std::cout << numerator << "/" << denominator;
}

Fraction add(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator + f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    });
}

// Fraction add(Fraction const& f1, Fraction const& f2) {
//     Fraction result {
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator
//         f1.denominator * f2.denominator
//     };

//     return simplify(result);
// }


Fraction sub(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator - f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    });
}

Fraction mul(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.numerator,
        f1.denominator * f2.denominator
    });
}

Fraction div(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator,
        f1.denominator * f2.numerator
    });
}

//exo1
// Fraction operator+(Fraction const& f1, Fraction const& f2) {
//     int new_num = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
//     int new_den = f1.denominator * f2.denominator;
//     return simplify(Fraction{new_num, new_den});
// }

// Fraction operator-(Fraction const& f1, Fraction const& f2) {
//     int new_num = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
//     int new_den = f1.denominator * f2.denominator;
//     return simplify(Fraction{new_num, new_den});
// }

// Fraction operator*(Fraction const& f1, Fraction const& f2) {
//     int new_num = f1.numerator * f2.numerator;
//     int new_den = f1.denominator * f2.denominator;
//     return simplify(Fraction{new_num, new_den});
// }

// Fraction operator/(Fraction const& f1, Fraction const& f2) {
//     int new_num = f1.numerator * f2.denominator;
//     int new_den = f1.denominator * f2.numerator;
//     return simplify(Fraction{new_num, new_den});
// }

//exo2
std::ostream& operator<<(std::ostream& os, Fraction const& f) {
    os << f.numerator;
    if (f.denominator != 1) {
        os << "/" << f.denominator;
    }
    return os;
}

//exo3
bool operator==(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator == f2.numerator * f1.denominator;
}

bool operator!=(Fraction const& f1, Fraction const& f2) {
    return !(f1 == f2);
}

//exo4
bool operator<(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator < f2.numerator * f1.denominator;
}

bool operator<=(Fraction const& f1, Fraction const& f2) {
    return f1 < f2 || f1 == f2;
}

bool operator>(Fraction const& f1, Fraction const& f2) {
    return !(f1 <= f2);
}

bool operator>=(Fraction const& f1, Fraction const& f2) {
    return !(f1 < f2);
}

//exo5
Fraction& Fraction::operator+=(Fraction const& f) {
    numerator = numerator * f.denominator + f.numerator * denominator;
    denominator = denominator * f.denominator;
    *this = simplify(*this);
    return *this;
}

Fraction& Fraction::operator-=(Fraction const& f) {
    numerator = numerator * f.denominator - f.numerator * denominator;
    denominator = denominator * f.denominator;
    *this = simplify(*this);
    return *this;
}

Fraction& Fraction::operator*=(Fraction const& f) {
    numerator = numerator * f.numerator;
    denominator = denominator * f.denominator;
    *this = simplify(*this);
    return *this;
}

Fraction& Fraction::operator/=(Fraction const& f) {
    numerator = numerator * f.denominator;
    denominator = denominator * f.numerator;
    *this = simplify(*this);
    return *this;
}

Fraction operator+(Fraction f1, Fraction const& f2) {
    f1 += f2;
    return f1;
}

Fraction operator-(Fraction f1, Fraction const& f2) {
    f1 -= f2;
    return f1;
}

Fraction operator*(Fraction f1, Fraction const& f2) {
    f1 *= f2;
    return f1;
}

Fraction operator/(Fraction f1, Fraction const& f2) {
    f1 /= f2;
    return f1;
}


//exo6
float Fraction::to_float() const {
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

Fraction::operator float() const {
    return to_float();
}

//pour aller plus loin
