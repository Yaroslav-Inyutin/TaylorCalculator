#include "ch.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::cosh, std::abs;

ChFunction::ChFunction(double k) : TaylorFunction(k) {}
ChFunction::~ChFunction() {}

double ChFunction::exactValue(double x) const {
    return cosh(coefficient * x);
}

double ChFunction::maclaurinTerm(unsigned n, double x) const {
    if (n % 2 == 1) return 0.0; // только чётные

    double kx = coefficient * x;
    return pow(kx, n) / factorial(n);
}

double ChFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double maxVal = cosh(k * abs(x));
    return pow(k, n) * maxVal;
}