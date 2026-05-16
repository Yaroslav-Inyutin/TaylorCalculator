#include "pow.hpp"
#include <cmath>
#include <iostream>

PowerFunction::PowerFunction(double alpha, double k) : TaylorFunction(k), alpha_(alpha) {}

double PowerFunction::exactValue(double x) const {
    return std::pow(1.0 + x, alpha_);
}

double PowerFunction::firstTerm(double x) const {
    return 1.0;
}

unsigned PowerFunction::firstDeg() const {
    return 0;
}

double PowerFunction::nextTerm(double prevTerm, unsigned prevN, double x) const {
    return prevTerm *(alpha_ - prevN) * x /(prevN + 1.0);
}

double PowerFunction::maxDerivative(unsigned n, double x) const {
    double base = abs(1.0 + x);
    double coeff = abs(alpha_);
    return pow(coeff, n) * pow(base, alpha_ - n);
}
