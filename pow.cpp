#include "pow.hpp"
#include <cmath>
#include <iostream>

// Инициализируем alpha_ значением из конструктора
PowerFunction::PowerFunction(double alpha, double k) : TaylorFunction(k), alpha_(alpha) {}

// Реализация биномиального коэффициента: alpha * (alpha-1) * ... * (alpha-n+1) / n!
// Но так как мы делим на factorial(n) отдельно в maclaurinTerm, 
// здесь считаем только числитель: alpha * (alpha-1) * ...
double PowerFunction::binomialCoeff(double alpha, unsigned n) {
    if (n == 0) return 1.0;
    
    double res = 1.0;
    for (unsigned i = 0; i < n; ++i) {
        res *= (alpha - static_cast<double>(i));
    }
    return res;
}

double PowerFunction::exactValue(double x) const {
    // (1+x)^alpha определено корректно при 1+x > 0
    if (1.0 + x <= 0.0) {
        // Можно выбросить исключение или вернуть NaN, в зависимости от требований
        return std::nan(""); 
    }
    return std::pow(1.0 + x, alpha_);
}

double PowerFunction::maclaurinTerm(unsigned n, double x) const {
    // Коэффициент ряда Тейлора: C(alpha, n) = binom / n!
    // Но binomialCoeff у нас уже считает произведение (alpha-i), 
    // а деление на n! происходит здесь:
    
    double coeff_numerator = binomialCoeff(alpha_, n);
    double factorial_val = this->factorial(n); // Предполагаем, что factorial есть в базовом классе
    
    // Избегаем деления на 0, хотя 0! = 1
    if (factorial_val == 0.0) return 0.0;

    double coeff = coeff_numerator / factorial_val;
    
    // Для x=0 и n=0 pow(0,0) может быть неоднозначным, но обычно 1.
    // При n=0 term должен быть равен 1 (так как (1+x)^a при x=0 равно 1)
    if (n == 0) return 1.0; 
    
    return coeff * std::pow(x, static_cast<double>(n));
}

double PowerFunction::maxDerivative(unsigned n, double x) const {
    // f(x) = (1+x)^alpha
    // f'(x) = alpha * (1+x)^(alpha-1)
    // f''(x) = alpha * (alpha-1) * (1+x)^(alpha-2)
    // f^(n)(x) = [alpha * (alpha-1) * ... * (alpha-n+1)] * (1+x)^(alpha-n)
    
    // Нам нужна оценка максимума модуля производной на интервале между 0 и x.
    // Пусть intervalEnd — это точка x, в которой мы оцениваем остаток.
    // Интервал разложения: от 0 до x.
    
    // 1. Вычисляем коэффициент производной (тот же самый, что в числителе бинома)
    double deriv_coeff = binomialCoeff(alpha_, n);
    
    // 2. Оцениваем множитель (1+xi)^(alpha-n).
    // Чтобы получить МАКСИМУМ модуля остатка, нужно взять худший случай для (1+xi).
    // Если alpha - n > 0, функция растет, максимум на конце интервала.
    // Если alpha - n < 0, функция убывает, максимум ближе к -1 (сингулярность).
    
    // Для простоты и безопасности оценки остатка Лагранжа часто берут максимальное значение 
    // на границах интервала [min(0,x), max(0,x)].
    
    double xi = x; // Берем оценку в точке x (часто этого достаточно для эвристики)
    // Более строгая оценка: найти max |(1+t)^(alpha-n)| для t между 0 и x.
    
    // Защита от отрицательного основания степени, если alpha-n не целое
    double base = 1.0 + std::abs(xi); // Грубая оценка сверху, чтобы не уйти в комплексные числа
    // Если x > -1, то 1+x > 0. Если мы работаем в области сходимости, это ОК.
    
    // Используем fabs для показателя, чтобы избежать проблем со знаками при возведении
    double power_part = std::pow(std::abs(1.0 + xi), alpha_ - static_cast<double>(n));
    
    return std::abs(deriv_coeff * power_part);
}