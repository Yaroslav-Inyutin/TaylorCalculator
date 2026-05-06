#include <cmath>
#include <iostream>
#include "get_accuracy.hpp"

get_accuracy::get_accuracy(std::shared_ptr<TaylorFunction> func) : func(func) {}

get_accuracy::~get_accuracy(){}

double get_accuracy::lagrangeRemainder(const double& x, const unsigned& n) const {
    double maxDeriv = func->maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / func->factorial(n+1));
}


double get_accuracy::getApproximation(const double& x, const unsigned& n){
    double approx=0;
    std::cout << "Начинаем аппроксимацию" << std::endl;
    for(int i=0; i<=n; i++){
        approx+=func->maclaurinTerm(i, x);
        std::cout << "Новое значение суммы: " << approx << std::endl << std::endl;
    }
    return approx;
}

double get_accuracy::compare_with_exactValue(const double& x, const unsigned& n){
    return std::abs(func->exactValue(x)-getApproximation(x, n));
}
