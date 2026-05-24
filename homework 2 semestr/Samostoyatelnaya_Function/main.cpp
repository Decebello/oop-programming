#include "functions.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string message = "--- Демонстрация работы классов функций ---";
    std::cout << message << std::endl;

    Hiperbola hip(4.0, 2.0);      
    Parabola par(1.0, -2.0, 1.0);  
    Exponenta exp_fn(1.0, 0.5, 0.0); 
    
    std::vector<double> poly_coeffs = {2.0, 0.0, -3.0, 1.0};
    Polinom poly(poly_coeffs);

    hip.printResult(2.0);
    par.printResult(2.0);
    exp_fn.printResult(2.0);
    poly.printResult(2.0);

    std::cout << "\nParabola min на [0.5, 3.0]: " << par.findMin(0.5, 3.0) << std::endl;
    std::cout << "Polinom max на [0.5, 3.0]: " << poly.findMax(0.5, 3.0) << std::endl;

    std::cout << "\nHiperbola integral на [1.0, 2.0]: " << hip.integrate(1.0, 2.0) << std::endl;
    std::cout << "Exponenta derivative в x = 2.0: " << exp_fn.differentiate(2.0) << std::endl;

    return 0;
}