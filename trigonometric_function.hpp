#pragma once
#include "taylor_function.hpp"

class TrigonometricFunction : public TaylorFunction{
protected:
    bool useReduction_ = false;
public:
    TrigonometricFunction(double k, double power, double outerCoefficient, bool useReduction);
    TrigonometricFunction(double k, double power, double outerCoefficient);
    double prepArg(double x) const override;
    bool isTrigonometric() const override;
};
