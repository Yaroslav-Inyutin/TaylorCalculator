#include "ln.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::log, std::abs;

LnFunction::LnFunction(double k) : TaylorFunction(k) {}
LnFunction::~LnFunction() {}

double LnFunction::exactValue(double x) const {
    return log(1 + x);
}

double LnFunction::maclaurinTerm(unsigned n, double x) const {
    if (n == 0) return 0.0;
    int sign = (n % 2 == 0) ? -1 : 1;
    return sign * pow(x, n) / n;
}

double LnFunction::maxDerivative(unsigned n, double x) const {
    // n-я производная ~ (n-1)! / (1+x)^n
    double denom = pow(1 + abs(x), n);
    return factorial(n - 1) / denom;
}