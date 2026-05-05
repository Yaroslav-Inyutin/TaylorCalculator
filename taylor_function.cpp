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
    // Эти строки выполняются ТОЛЬКО при первом вызове функции:
    static unsigned long long int cacheInt[MAX_EXACT_FACTORIAL + 1];
    static double cacheDouble[150];
    static bool initialized = false;
    
    if (!initialized) {
        cacheInt[0] = 1;
        for (unsigned i = 1; i <= MAX_EXACT_FACTORIAL; i++) {
            cacheInt[i] = cacheInt[i-1] * i;
        }
        cacheDouble[0] = cacheInt[20] * 21;
        for(unsigned i=22; i<=170; i++){
            cacheDouble[i-21] = cacheDouble[i-22] * i;
        }
        // отладочный вывод кэша
        // std::cout << "in cache now: " << std::endl;
        // for(int i=0; i<=20; i++){
        //     std::cout << "i = " << i << ", factorial = " << cacheInt[i] << std::endl;
        // }
        // for(int i=0; i<=149; i++){
        //     std::cout << "i = " << i+21 << ", factorial = " << cacheDouble[i] << std::endl;
        // }
        initialized = true;
    }
    // Если есть в кэше — возвращаем точное значение с приведением
    if (n <= MAX_EXACT_FACTORIAL) return static_cast<double>(cacheInt[n]);
    
    // Если больше 20! — считаем в double, 
    // unsigned long long переполнен, так что нет иных вариантов, кроме как накапливать ошибку doubl а
    return cacheDouble[n-21];
}

double TaylorFunction::lagrangeRemainder(unsigned n, double x) const {
    double maxDeriv = maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / factorial(n+1));
}


double TaylorFunction::getApproximation(const double x, const unsigned n) const{
    double approx=0;
    std::cout << "Начинаем аппроксимацию" << std::endl;
    for(int i=0; i<=n; i++){
        approx+=maclaurinTerm(i, x);
        std::cout << "Новое значение суммы: " << approx << std::endl << std::endl;
    }
    return approx;
}

double TaylorFunction::compare_with_exactValue(const double x, const unsigned n) const{
    return std::abs(exactValue(x)-getApproximation(x, n));
}
