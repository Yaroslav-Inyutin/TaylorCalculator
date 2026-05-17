#include "trigonometric_function.hpp"
#include <iostream>
#include <cmath>
#include <numbers>
TrigonometricFunction::TrigonometricFunction(double k, bool useReduction) : TaylorFunction(k), useReduction_(useReduction){}
double TrigonometricFunction::prepArg(double x) const{
    if(!useReduction_) return x;
    double reduced = std::remainder(coefficient * x, 2.0 * std::numbers::pi);
    return reduced / coefficient;
}
bool TrigonometricFunction::isTrigonometric() const {
	return true;
}
