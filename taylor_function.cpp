#include "taylor_function.hpp"
#include <cmath>
#include <iostream>

TaylorFunction::TaylorFunction(double k) : coefficient(k) {}

TaylorFunction::~TaylorFunction() = default;

double TaylorFunction::prepArg(double x) const{
	return x;
}
bool TaylorFunction::isTrigonometric() const {
	return false;
}
// double TaylorFunction::getCoefficient() const {
//     return coefficient;
// }

// Static метод - общий для всех экземпляров
