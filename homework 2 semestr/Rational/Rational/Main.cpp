#include <iostream>
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
