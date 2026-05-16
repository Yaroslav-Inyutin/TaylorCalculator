#include "ln.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::log, std::abs;

LnFunction::LnFunction(double k) : TaylorFunction(k) {}
LnFunction::~LnFunction() {}

double LnFunction::exactValue(double x) const {
    return log(1 + x);
}

double LnFunction::firstTerm(double x) const {
    return x;
}

unsigned LnFunction::firstDeg() const {
    return 1;
}

double LnFunction::nextTerm(double prevTerm, unsigned prevN, double x) const {
    return -prevTerm * (prevN / (prevN + 1.0)) * x;
}

double LnFunction::maxDerivative(unsigned n, double x) const {
    double denom = pow(1 + abs(x), n);
    return std::tgamma(n) / denom;
}
