#pragma once
#include "taylor_function.hpp"

class ShFunction : public TaylorFunction {
public:
    explicit ShFunction(double k = 1.0);
    ~ShFunction() override;

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};