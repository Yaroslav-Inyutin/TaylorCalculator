#include "taylor_function.hpp"
#include <cmath>
#include <iostream>

TaylorFunction::TaylorFunction(double k) : coefficient(k) {}

TaylorFunction::~TaylorFunction() {}

// double TaylorFunction::getCoefficient() const {
//     return coefficient;
// }

// Static метод - общий для всех экземпляров
double TaylorFunction::factorial(unsigned n) {
    // Кэш хранится точно в целочисленном типе
    static unsigned long long int cache[MAX_EXACT_FACTORIAL + 1];
    static bool initialized = false;
    
    if (!initialized) {
        cache[0] = 1;
        for (unsigned i = 1; i <= MAX_EXACT_FACTORIAL; i++) {
            cache[i] = cache[i-1] * i;
        }
        initialized = true;
    }
    
    // Если есть в кэше — возвращаем точное значение с приведением
    if (n <= MAX_EXACT_FACTORIAL) return static_cast<double>(cache[n]);
    
    // Если больше 20! — считаем в double, 
    // unsigned long long переполнен, так что нет иных вариантов, кроме как накапливать ошибку doubl а
    double result = static_cast<double>(cache[MAX_EXACT_FACTORIAL]);
    for (unsigned i = MAX_EXACT_FACTORIAL + 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double TaylorFunction::lagrangeRemainder(unsigned n, double x) const {
    double maxDeriv = maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / factorial(n+1));
}


double TaylorFunction::getApproximation(const double x, const unsigned n) const{
    double approx=0;
    // std::cout << "Начинаем аппроксимацию" << std::endl;
    for(int i=0; i<=n; i++){
        approx+=maclaurinTerm(i, x);
        // std::cout << "Новое значение суммы: " << approx << std::endl;
    }
    return approx;
}

double TaylorFunction::compare_with_exactValue(const double x, const unsigned n) const{
    return std::abs(exactValue(x)-getApproximation(x, n));
}
