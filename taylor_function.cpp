#include "taylor_function.hpp"
#include <cmath>

SeriesFunction::SeriesFunction(double k) : coefficient(k) {}

SeriesFunction::~SeriesFunction() {}

double SeriesFunction::lagrangeRemainder(unsigned n, double x) const {
    double maxDeriv = maxDerivative(n + 1, x);
    double factorial = 1.0;
    for (unsigned i=1; i<=n+1; i++) {
        factorial *= i;
    }
    return std::abs(maxDeriv * std::pow(x, n + 1) / factorial);
}

double SeriesFunction::getCoefficient() const {
    return coefficient;
}