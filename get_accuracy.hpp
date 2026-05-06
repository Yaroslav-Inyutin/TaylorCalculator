#pragma once
#include "taylor_function.hpp"
#include <memory>

class get_accuracy {
private:
    std::shared_ptr<TaylorFunction> func;
public:
    get_accuracy(std::shared_ptr<TaylorFunction> func);
    ~get_accuracy(){};

    // аппроксимировать функцию по Тейлору
    double getApproximation(const double& x, const unsigned& n); // не const в суффиксе, потому что переопределяет поле approximation
    // сравнить аппроксимацию с cmath
    double compare_with_exactValue(const double& x, const unsigned& n); // не перегружаются, не virtual. тоже не const, потому что использует getApproximation
    // вычислить остаточный член в форме Лагранжа
    double lagrangeRemainder(const double& x, const unsigned& n) const; // тоже не будет перегружаться
};