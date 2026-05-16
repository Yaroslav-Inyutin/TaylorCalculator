#pragma once
#include "trigonometric_function.hpp"
#include <numbers>

class SinFunction : public TrigonometricFunction { 
public:
    explicit SinFunction(double k = 1.0, bool useReduction = true);
    ~SinFunction() override;
    
    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double x) const override;
};
