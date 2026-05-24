#include "functions.h"
#include <iostream>
#include <cmath>

double Function::findMin(double start, double end) const {
    double step = (end - start) / 10000.0;
    double min_val = evaluate(start);
    for (double x = start + step; x <= end; x += step) {
        double y = evaluate(x);
        if (y < min_val) {
            min_val = y;
        }
    }
    return min_val;
}

double Function::findMax(double start, double end) const {
    double step = (end - start) / 10000.0;
    double max_val = evaluate(start);
    for (double x = start + step; x <= end; x += step) {
        double y = evaluate(x);
        if (y > max_val) {
            max_val = y;
        }
    }
    return max_val;
}

double Function::integrate(double start, double end) const {
    int n = 10000;
    double h = (end - start) / n;
    double sum = 0.5 * (evaluate(start) + evaluate(end));
    for (int i = 1; i < n; ++i) {
        sum += evaluate(start + i * h);
    }
    return sum * h;
}

double Function::differentiate(double x) const {
    double h = 1e-5;
    return (evaluate(x + h) - evaluate(x - h)) / (2.0 * h);
}

Hiperbola::Hiperbola(double k_val, double c_val) : k(k_val), c(c_val) {}

double Hiperbola::evaluate(double x) const {
    if (x == 0.0) {
        return 0.0; 
    }
    return k / x + c;
}

void Hiperbola::printResult(double x) const {
    std::cout << "Hiperbola f(" << x << ") = " << evaluate(x) << std::endl;
}

Parabola::Parabola(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {}

double Parabola::evaluate(double x) const {
    return a * x * x + b * x + c;
}

void Parabola::printResult(double x) const {
    std::cout << "Parabola f(" << x << ") = " << evaluate(x) << std::endl;
}

Exponenta::Exponenta(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {}

double Exponenta::evaluate(double x) const {
    return a * std::exp(b * x) + c;
}

void Exponenta::printResult(double x) const {
    std::cout << "Exponenta f(" << x << ") = " << evaluate(x) << std::endl;
}

Polinom::Polinom(const std::vector<double>& coeffs) : coefficients(coeffs) {}

double Polinom::evaluate(double x) const {
    double result = 0.0;
    for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; --i) {
        result = result * x + coefficients[i];
    }
    return result;
}

void Polinom::printResult(double x) const {
    std::cout << "Polinom f(" << x << ") = " << evaluate(x) << std::endl;
}