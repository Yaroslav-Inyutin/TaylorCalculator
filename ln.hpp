#pragma once
#include "taylor_function.hpp"

class LnFunction : public TaylorFunction {
public:
    explicit LnFunction(double k = 1.0);
    ~LnFunction() override;

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};