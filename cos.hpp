#pragma once
#include "taylor_function.hpp"

class CosFunction : public TaylorFunction {
public:
    explicit CosFunction(double k = 1.0);
    ~CosFunction() override;

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};