#include "sh.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::sinh, std::abs;

ShFunction::ShFunction(double k) : TaylorFunction(k) {}
ShFunction::~ShFunction() {}

double ShFunction::exactValue(double x) const {
    return sinh(coefficient * x);
}

double ShFunction::maclaurinTerm(unsigned n, double x) const {
    if (n % 2 == 0) return 0.0; // только нечётные

    double kx = coefficient * x;
    return pow(kx, n) / factorial(n);
}

double ShFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double maxVal = sinh(k * abs(x));
    return pow(k, n) * maxVal;
}