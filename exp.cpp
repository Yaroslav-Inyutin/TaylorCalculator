#include "exp.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::exp, std::abs;

ExpFunction::ExpFunction(double k, double power, double outerCoefficient) : TaylorFunction(k, power, outerCoefficient) {}
ExpFunction::~ExpFunction() {}

double ExpFunction::exactValue(double x) const {
    return exp(coefficient * x);
}

double ExpFunction::firstTerm(double x) const {
    (void)x;
    return 1.0;
}

unsigned ExpFunction::firstDeg() const {
    return 0;
}

double ExpFunction::nextTerm(double prevTerm, unsigned prevN, double x) const {
    double kx = coefficient * x;
    return prevTerm * (kx / (prevN + 1.0));
}

double ExpFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    return pow(k, n) * exp(k * abs(x));
}
