#pragma once
#include "taylor_function.hpp"

class LnFunction : public TaylorFunction {
public:
    explicit LnFunction(double k = 1.0, double power, double outerCoefficient);
    ~LnFunction() override;
    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};
