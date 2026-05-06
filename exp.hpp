#pragma once
#include "taylor_function.hpp"

class ExpFunction : public TaylorFunction {
public:
    explicit ExpFunction(double k = 1.0);
    ~ExpFunction() override;

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};