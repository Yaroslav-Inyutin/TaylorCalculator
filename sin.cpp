#include "sin.hpp"
#include <iostream>
#include <cmath>

SinFunction::SinFunction(double k) : TaylorFunction(k) {}

SinFunction::~SinFunction(){}

double SinFunction::exactValue(double x) const {
    return std::sin(coefficient * x);
}

double SinFunction::maclaurinTerm(unsigned n, double x) const {
    if (n % 2 == 0) return 0.0;  // Чётные члены = 0
    
    unsigned m = (n - 1) / 2; // тут уже работаем с нечётными. m нужен только для поиска знака
    double y = coefficient * x;
    double sign = (m % 2 == 0) ? 1.0 : -1.0;
    // std::cout << "Член разложения: " << n << std::endl << "Значение слагаемого : " << sign * std::pow(y, n) / factorial(n);
    return sign * std::pow(y, n) / factorial(n);
} // это как будто бы и не нужно будет, только если с exactValue сравнивать напрямую

double SinFunction::maxDerivative(unsigned n, double x) const {
    double k = std::abs(coefficient);
    double absX = std::abs(x);
    
    // Нечётные производные: содержат cos, его максимум = 1. Это, кстати, плохо. Возможно, следует бросать варнинг пользователю.
    if (n % 2 == 1) {
        return std::pow(k, n);
    }
    
    // Чётные производные: sin
    // |sin(kx)| ≤ |kx| верно ∀x, но уточнённая оценка выгодна только при |kx| < 1
    // Чтобы это чаще было так, можно повыкидывать 2pi из kx
    // Fовыкидываем 2pi:
    double kx = k*absX;
    while(kx > 2 * std::numbers::pi){
        kx-=2 * std::numbers::pi;
    }
    double tightBound = std::pow(k, n) * kx;
    double conservativeBound = std::pow(k, n);
    
    return std::min(tightBound, conservativeBound);
}

// std::string SinFunction::name() const {
//     if (coefficient == 1.0) {
//         return "sin(x)";
//     }
//     return "sin(" + std::to_string(coefficient) + "x)"; // std::to_string - явное преобразование типов
// }