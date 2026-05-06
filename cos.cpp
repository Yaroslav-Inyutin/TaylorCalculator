#include "cos.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs;

CosFunction::CosFunction(double k) : TaylorFunction(k) {}
CosFunction::~CosFunction() {}

double CosFunction::exactValue(double x) const {
    return std::cos(coefficient * x);
}

double CosFunction::maclaurinTerm(unsigned n, double x) const {
    if (n % 2 == 1) return 0.0; // нечётные = 0

    unsigned m = n / 2;
    double kx = coefficient * x;
    int sign = (m % 2 == 0) ? 1 : -1;

    return sign * pow(kx, n) / factorial(n);
}

double CosFunction::maxDerivative(unsigned n, double x) const {
    return pow(abs(coefficient), n); // как у sin для нечётных
}