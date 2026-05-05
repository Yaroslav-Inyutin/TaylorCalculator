#pragma once
#include "taylor_function.hpp"

class SinFunction : public TaylorFunction { 
public:
    explicit SinFunction(double k = 1.0);
    ~SinFunction() override;
    
    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
    
private:
    
};