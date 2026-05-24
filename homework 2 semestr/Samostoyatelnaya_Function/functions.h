#pragma once 

#include <vector>
#include <string>

class Function {
public:
    virtual ~Function() {}
    
    virtual double evaluate(double x) const = 0;
    virtual void printResult(double x) const = 0;
    virtual double findMin(double start, double end) const;
    virtual double findMax(double start, double end) const;
    virtual double integrate(double start, double end) const;
    virtual double differentiate(double x) const;
};

class Hiperbola : public Function {
private:
    double k, c;
public:
    Hiperbola(double k_val, double c_val);
    double evaluate(double x) const override;
    void printResult(double x) const override;
};

class Parabola : public Function {
private:
    double a, b, c;
public:
    Parabola(double a_val, double b_val, double c_val);
    double evaluate(double x) const override;
    void printResult(double x) const override;
};

class Exponenta : public Function {
private:
    double a, b, c;
public:
    Exponenta(double a_val, double b_val, double c_val);
    double evaluate(double x) const override;
    void printResult(double x) const override;
};

class Polinom : public Function {
private:
    std::vector<double> coefficients; 
public:
    Polinom(const std::vector<double>& coeffs);
    double evaluate(double x) const override;
    void printResult(double x) const override;
};