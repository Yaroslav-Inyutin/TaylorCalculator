#include <cmath>
#include <iostream>
#include "calculator.hpp"
#degine THRESHOLD 1e-300
Calculator::Calculator(std::shared_ptr<TaylorFunction> func) : func(func) {}

Calculator::~Calculator(){}

double Calculator::lagrangeRemainder(const double& x, const unsigned& n) const {
    double maxDeriv = func->maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / func->factorial(n+1));
}


double Calculator::approximation(const double& x, const unsigned& n){
    double approx=0;
    std::cout << "Начинаем аппроксимацию" << std::endl;
    for(int i=0; i<=n; i++){
        approx+=func->maclaurinTerm(i, x);
        std::cout << "Новое значение суммы: " << approx << std::endl << std::endl;
    }
    return approx;
}

double Calculator::compare_with_exactValue(const double& x, const unsigned& n){
    return std::abs(func->exactValue(x)-approximation(x, n));
}

void Calculator::setNewfunc(std::shared_ptr<TaylorFunction> func){
    this->func=func;
}
unsigned Calculator::degree(const double& x, const double& accuracy) const{
    double cur_acc;
    unsigned deg=0;
    for(deg<=func->MAX_FACTORIAL; deg++){
        cur_acc = lagrangeRemainder(x, accuracy);
        if(cur_acc - accuracy <= THRESHOLD) return deg;
    }
    throw std::runtime_error("Не удалось достигнуть требуемой точности") // тоже позже перепишу какой тут эррор
}