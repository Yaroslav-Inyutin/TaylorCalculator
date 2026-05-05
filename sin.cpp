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
    double kx = coefficient * x;
    double sign = (m % 2 == 0) ? 1.0 : -1.0;
    // std::cout << "Член разложения: " << n << std::endl << "Значение слагаемого : " << sign * std::pow(y, n) / factorial(n);
    return sign * std::pow(kx, n) / factorial(n);
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

// std::string SinFunction::name() const {
//     if (coefficient == 1.0) {
//         return "sin(x)";
//     }
//     return "sin(" + std::to_string(coefficient) + "x)"; // std::to_string - явное преобразование типов
// }