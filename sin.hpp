#pragma once
#include "taylor_function.hpp"
#include <numbers>

class SinFunction : public TaylorFunction { 
public:
    explicit SinFunction(double k = 1.0);
    ~SinFunction() override;
    
    double exactValue(double x) const override;
    double maclaurinTerm(const unsigned& n, const double& x) const override;
    double maxDerivative(const unsigned& n, const double& x) const override;
    // double removePis(double x);
};