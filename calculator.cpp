#include <cmath>
#include <iostream>
#include "calculator.hpp"
static constexpr unsigned MAX_DEGREE = 200;
#define THRESHOLD 1e-200

Calculator::Calculator(std::shared_ptr<SumFunction> func) : func(func) {}

Calculator::~Calculator(){}

double Calculator::lagrangeRemainder(double x, unsigned n) const {
    double maxDeriv = func->maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / std::tgamma(n+2)); //std::tgamma(x) возвращает факториал от x-1
}

double Calculator::approximation(double x, unsigned n) const{
    double approx=0.0;
    for(const auto& elem : func->terms){
        if(x==0 && elem->getPower()<0) 

        x = elem->prepArg(x); // приводит аргумент к оптимальному, если того захотел пользователь
        unsigned curDeg = elem->firstDeg();
        if (curDeg > n) return 0.0;
        double term = elem->firstTerm(x);
        double sum = term;
        while(curDeg + 1 <= n){
            term = func->nextTerm(term, curDeg, x);
            curDeg+= 1; // тут надо подумать что делать с тригонометрическими функциями, там у них должна быть двойка, вроде как
            sum += term;
            }
        approx+=sum * elem->getOuterCoefficient() * pow(x, elem->getPower());
        // std::cout << "Аппрокимация : " << approx << std::endl;
    }
    return approx;
}

double Calculator::compare_with_exactValue(double x, unsigned n) const{
    return std::abs(func->exactValue(x)-approximation(x, n));
}

void Calculator::setNewfunc(std::shared_ptr<SumFunction> func){
    this->func=func;
}
unsigned Calculator::degree(double x, double accuracy) const{
    double cur_acc;
    unsigned deg=0;
    for(; deg<=MAX_DEGREE; deg++){
        cur_acc = lagrangeRemainder(x, deg);
        if(cur_acc - accuracy <= THRESHOLD) return deg;
    }
    throw accuracy_error("Не удалось достигнуть требуемой точности. Снизьте точность или приблизьте x к нулю."); 
}
double Calculator::right_intervalEnd(double dx, double accuracy, unsigned n) const{
    if(dx < 1e-10) throw accuracy_error("Задана слишком высокая точность вычисления границы интервала. Снизьте точность до 10^-10"); 
    double border=0.0;
    for(; lagrangeRemainder(border, n)<=accuracy; border+=dx){};
    return border;
}
double Calculator::right_intervalEnd(double dx, double accuracy) const{
    return right_intervalEnd(dx, accuracy, MAX_DEGREE);
}
double Calculator::left_intervalEnd(double dx, double accuracy, unsigned n) const{
    if(dx < 1e-10) throw accuracy_error("Задана слишком высокая точность вычисления границы интервала. Снизьте точность до 10^-10");
    double border=0.0;
    for(; lagrangeRemainder(border, n)<=accuracy; border-=dx){};
    return border;
}
double Calculator::left_intervalEnd(double dx, double accuracy) const{
    return left_intervalEnd(dx, accuracy, MAX_DEGREE);
}
borders Calculator::interval(double dx, double accuracy, unsigned n) const{
    return {left_intervalEnd(dx, accuracy, n), right_intervalEnd(dx, accuracy, n)};
}
borders Calculator::interval(double dx, double accuracy) const{
    return interval(dx, accuracy, MAX_DEGREE);
}
