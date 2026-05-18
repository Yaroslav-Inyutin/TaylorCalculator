#pragma once
#include "taylor_function.hpp"

class ShFunction : public TaylorFunction {
public:
    explicit ShFunction(double k, double power, double outerCoefficient);
    ~ShFunction() override;
    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double x) const override;
};
