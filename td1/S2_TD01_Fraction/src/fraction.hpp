#pragma once
#include <iostream>
#include <cmath>

struct Fraction {
    int numerator { 0 };
    int denominator { 1 };

    void display();

    //exo5
    Fraction& operator+=(Fraction const& f);
    Fraction& operator-=(Fraction const& f);
    Fraction& operator*=(Fraction const& f);
    Fraction& operator/=(Fraction const& f);

    //exo6
    float to_float() const;
    operator float() const;
};

Fraction add(Fraction const& f1, Fraction const& f2);
Fraction sub(Fraction const& f1, Fraction const& f2);
Fraction mul(Fraction const& f1, Fraction const& f2);
Fraction div(Fraction const& f1, Fraction const& f2);

//exo1
Fraction operator+(Fraction const& f1, Fraction const& f2);
Fraction operator-(Fraction const& f1, Fraction const& f2);
Fraction operator*(Fraction const& f1, Fraction const& f2);
Fraction operator/(Fraction const& f1, Fraction const& f2);

//exo2
std::ostream& operator<<(std::ostream& os, Fraction const& f);

//exo3
bool operator==(Fraction const& f1, Fraction const& f2);
bool operator!=(Fraction const& f1, Fraction const& f2);

//exo4
bool operator<(Fraction const& f1, Fraction const& f2);
bool operator<=(Fraction const& f1, Fraction const& f2);
bool operator>(Fraction const& f1, Fraction const& f2);
bool operator>=(Fraction const& f1, Fraction const& f2);

//pour aller plus loin
Fraction operator+(Fraction const& f, int const i);
Fraction operator+(int const i, Fraction const& f);

Fraction operator-(Fraction const& f, int const i);
Fraction operator-(int const i, Fraction const& f);

Fraction operator*(Fraction const& f, int const i);
Fraction operator*(int const i, Fraction const& f);

Fraction operator/(Fraction const& f, int const i);
Fraction operator/(int const i, Fraction const& f);

