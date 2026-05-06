#include "pow.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs;

PowerFunction::PowerFunction(double alpha)
    : TaylorFunction(1.0), alpha(alpha) {}

PowerFunction::~PowerFunction() {}

double PowerFunction::exactValue(double x) const {
    return pow(1 + x, alpha);
}

double binomialCoeff(double alpha, unsigned n) {
    double res = 1.0;
    for (unsigned i = 0; i < n; ++i) {
        res *= (alpha - i);
    }
    return res;
}

double PowerFunction::maclaurinTerm(unsigned n, double x) const {
    double coeff = binomialCoeff(alpha, n) / factorial(n);
    return coeff * pow(x, n);
}

double PowerFunction::maxDerivative(unsigned n, double x) const {
    return factorial(n) * pow(1 + abs(x), alpha - n);
}