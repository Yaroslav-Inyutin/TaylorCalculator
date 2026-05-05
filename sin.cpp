#include "sin.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs;

SinFunction::SinFunction(double k) : TaylorFunction(k) {}

SinFunction::~SinFunction(){}

double SinFunction::exactValue(double x) const {
    return std::sin(coefficient * x);
}

double SinFunction::maclaurinTerm(unsigned n, double x) const {
    if (n % 2 == 0) return 0.0;  // Чётные члены = 0
    double kx = coefficient * x;
    // std::cout << "Член разложения: " << n << std::endl << "Значение слагаемого : " << sign * std::pow(y, n) / factorial(n);
    return pow(-1, n-1) * pow(kx, n) / factorial(n);
} // это как будто бы и не нужно будет, только если с exactValue сравнивать напрямую

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
    while(kx > std::numbers::pi){
        kx -= std::numbers::pi;
        // std::cout << "kx = " << kx << std::endl;
    }
    // sin(kx) = sin(pi-kx)
    kx = std::min(kx, std::numbers::pi-kx);
    // std::cout << "kx = " << kx << std::endl;
    double tightBound = std::pow(k, n) * kx;
    double conservativeBound = std::pow(k, n);
    
    return std::min(tightBound, conservativeBound);
}