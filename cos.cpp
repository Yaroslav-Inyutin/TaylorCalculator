#include "cos.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs;

CosFunction::CosFunction(double k) : TaylorFunction(k) {}
CosFunction::~CosFunction() {}

double CosFunction::exactValue(double x) const {
    return std::cos(coefficient * x);
}

double CosFunction::firstTerm(double x) const{
    return 1.0;
}

unsigned CosFunction::firstDeg() const
{
    return 0;
}

double CosFunction::nextTerm(double prevTerm, unsigned prevN, double x) const{
    double kx = coefficient * x;
    return prevTerm * (-kx * kx /((prevN + 1.0) * (prevN + 2.0)));
}
double CosFunction::maxDerivative(unsigned n, double x) const {
    return pow(abs(coefficient), n); // как у sin для нечётных
}
