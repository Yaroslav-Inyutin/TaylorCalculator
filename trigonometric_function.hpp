#pragma once
#include "taylor_function.hpp"

class TrigonometricFunction : public TaylorFunction{
protected:
    bool useReduction_;
public:
    TrigonometricFunction(double k, bool useReduction = true);
    double prepArg(double x) const override;
};
