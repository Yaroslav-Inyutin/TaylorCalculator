#include <cmath>
#include <iostream>
#include "calculator.hpp"

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
double Calculator::degree(const double& accuracy, const double& x) const{

}