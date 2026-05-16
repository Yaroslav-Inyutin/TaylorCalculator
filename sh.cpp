#include "sh.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::sinh, std::abs;

ShFunction::ShFunction(double k) : TaylorFunction(k) {}
ShFunction::~ShFunction() {}

double ShFunction::exactValue(double x) const {
    return sinh(coefficient * x);
}

double ShFunction::firstTerm(double x) const {
    return coefficient * x;
}

unsigned ShFunction::firstDeg() const {
    return 1;
}

double ShFunction::nextTerm(double prevTerm, unsigned prevN, double x) const {
    double kx = coefficient * x;
    return prevTerm * (	kx * kx /((prevN + 1.0) * (prevN + 2.0)));
}

double ShFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double maxVal = sinh(k * abs(x));
    return pow(k, n) * maxVal;
}
