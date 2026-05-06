#include "sin.hpp"
#include <iostream>
#include <cmath>
using std::pow, std::abs, std::min;
double pi=std::numbers::pi;

SinFunction::SinFunction(double k) : TaylorFunction(k) {}

SinFunction::~SinFunction(){}

double SinFunction::exactValue(double x) const {
    return std::sin(coefficient * x);
}

double SinFunction::maclaurinTerm(const unsigned& n, const double& x) const {
    if (n % 2 == 0) return 0.0;  // Чётные члены = 0

    unsigned m = (n - 1) / 2; // тут уже работаем с нечётными. m нужен только для поиска знака
    double kx = coefficient * x;
    int sign = (m % 2 == 0) ? 1 : -1;

    std::cout << "Член разложения: " << n << std::endl << "Факториал: " << factorial(n) << std::endl << "(kx)^n : " << pow(kx, n)
    << std::endl << "Значение слагаемого: " << sign * std::pow(kx, n) / factorial(n) << std::endl;
    return sign * pow(kx, n) / factorial(n);
} // это как будто бы и не нужно будет, только если с exactValue сравнивать напрямую

double SinFunction::maxDerivative(const unsigned& n, const double& x) const {
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