#pragma once
#include "trigonometric_function.hpp"

class CosFunction : public TrigonometricFunction {
public:
    explicit CosFunction(double k, double power, double outerCoefficient, bool useReduction = true);
    explicit CosFunction(double k, double power, double outerCoefficient);
    ~CosFunction() override;

    double exactValue(double x) const override;
    double firstTerm(double x) const override;
    unsigned firstDeg() const override;
    double nextTerm(double prevTerm, unsigned prevN, double x) const override;
    double maxDerivative(unsigned n, double intervalEnd) const override;
};
