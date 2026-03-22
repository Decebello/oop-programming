#include "rational.h"
#include <cmath>
#include <iostream>

Rational::Rational() {
    numer = 0; 
    denom = 1; 
}

Rational::Rational(int number) {
    numer = number; 
    denom = 1; 
}

Rational::Rational(int n, int d) {
    numer = n; 
    denom = d; 
    simplify();
}

void Rational::simplify() {
    if (denom < 0) {
        numer = -numer; 
        denom = -denom; 
    }
    for (int i = 2; i <= std::abs(denom) && i <= std::abs(numer); i++) {
        if (numer % i == 0 && denom % i == 0) {
            numer /= i; 
            denom /= i; 
            i--; 
        }
    }
}

Rational& Rational::operator +=(const Rational& r) {
    numer = (numer * r.denom + denom * r.numer); 
    denom *= r.denom; 
    simplify(); 
    return *this; 
}

Rational Rational::operator +(const Rational& r) const {
    Rational res(*this); 
    return res += r; 
}

Rational Rational::operator -() const {
    Rational r(-numer, denom); 
    return r; 
}

Rational& Rational::operator -=(const Rational& r) {
    return (*this += (-r)); 
}

Rational& Rational::operator ++() {
    numer += denom; 
    return *this; 
}

Rational Rational::operator ++(int) {
    Rational r(*this); 
    numer += denom; 
    return r; 
}

bool Rational::operator ==(const Rational& r) const {
    return (numer == r.numer) && (denom == r.denom); 
}

bool Rational::operator !=(const Rational& r) const {
    return !(*this == r); 
}

Rational::operator int() const {
    return numer / denom; 
}

Rational::operator double() const {
    return ((double)numer) / denom; 
}

std::istream& operator >>(std::istream& in, Rational& r) {
    in >> r.numer >> r.denom; 
    r.simplify();
    return in; 
}

std::ostream& operator <<(std::ostream& out, const Rational& r) {
    out << r.numer << "/" << r.denom; 
    return out; 
}

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian"); 
    Rational a(1, 2), b(-1, 6);
    cout << "a = " << a << ", b = " << b << endl;

    cout << "a + b = " << a + b << endl;

    double val = (double)a;
    cout << "a as double = " << val << endl;

    Rational g;
    cout << "Enter rational (numer denom): ";
    cin >> g;
    cout << "You entered: " << g << endl;

    return 0;
}
