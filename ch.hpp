#pragma once
#include "taylor_function.hpp"

class ChFunction : public TaylorFunction {
public:
    explicit ChFunction(double k, double power, double outerCoefficient);
    ~ChFunction() override;
    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double x) const override;
};
