#include "sin.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs, std::min, std::numbers::pi;
SinFunction::SinFunction(double k, bool useReduction) : TrigonometricFunction(k, useReduction) {}

SinFunction::~SinFunction(){}

double SinFunction::exactValue(double x) const {
    return std::sin(coefficient * x);
}

double SinFunction::firstTerm(double x) const{
	return coefficient * x;
}

unsigned SinFunction::firstDeg() const{
	return 1;
}

double SinFunction::nextTerm(double prevTerm, unsigned prevN, double x) const{
	double kx = coefficient * x;
	return prevTerm * (-kx * kx /((prevN + 1.0) * (prevN + 2.0)));
}

double SinFunction::maxDerivative(unsigned n, double x) const {
    double k = abs(coefficient);
    double absX = abs(x);
    
    // Нечётные производные: содержат cos, его максимум = 1.
    // Это, кстати, плохо. Возможно, следует бросать варнинг пользователю, чтобы он 
    if (n % 2 == 1) {
        return pow(k, n);
    }
    
    // Чётные производные: sin
    // |sin(kx)| ≤ |kx| верно ∀x, но уточнённая оценка выгодна только при |kx| < 1
    // Чтобы это чаще было так, можно повыкидывать pi из kx
    // Повыкидываем pi:
    double kx = k*absX;
    while(kx > pi){
        kx -= pi;
        // std::cout << "kx = " << kx << std::endl;
    }
    // sin(kx) = sin(pi-kx)
    kx = min(kx, pi-kx);
    // std::cout << "kx = " << kx << std::endl;
    double tightBound = pow(k, n) * kx;
    double conservativeBound = pow(k, n);
    
    return min(tightBound, conservativeBound);
}
