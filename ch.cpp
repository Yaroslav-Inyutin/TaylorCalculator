#include "ch.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::cosh, std::abs;

ChFunction::ChFunction(double k) : TaylorFunction(k) {}
ChFunction::~ChFunction() {}

double ChFunction::exactValue(double x) const {
    return cosh(coefficient * x);
}

double ChFunction::firstTerm(double x) const {
    return 1.0;
}

unsigned ChFunction::firstDeg() const {
    return 0;
}

double ChFunction::nextTerm(double prevTerm, unsigned prevN, double x) const {
    double kx = coefficient * x;
    return prevTerm * (kx * kx /((prevN + 1.0) * (prevN + 2.0)));
}

double ChFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double maxVal = cosh(k * abs(x));
    return pow(k, n) * maxVal;
}
