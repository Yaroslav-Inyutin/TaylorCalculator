#include "exp.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::exp, std::abs;

ExpFunction::ExpFunction(double k) : TaylorFunction(k) {}
ExpFunction::~ExpFunction() {}

double ExpFunction::exactValue(double x) const {
    return exp(coefficient * x);
}

double ExpFunction::maclaurinTerm(unsigned n, double x) const {
    double kx = coefficient * x;
    return pow(kx, n) / factorial(n);
}

double ExpFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double maxExp = exp(k * abs(x));
    return pow(k, n) * maxExp;
}