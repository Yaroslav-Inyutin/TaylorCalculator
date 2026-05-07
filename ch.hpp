#pragma once
#include "taylor_function.hpp"

class ChFunction : public TaylorFunction {
public:
    explicit ChFunction(double k = 1.0);
    ~ChFunction() override;

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};