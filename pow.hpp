#pragma once
#include "taylor_function.hpp"

class PowerFunction : public TaylorFunction {
private:
    double alpha_; //показатель степени
public:
    explicit PowerFunction(double alpha, double k, double power, double outerCoefficient);
    ~PowerFunction() override = default;
    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double x) const override;
};
