#include <cmath>
#include <iostream>
#include "calculator.hpp"
static constexpr unsigned MAX_DEGREE = 200;
#define THRESHOLD 1e-200

Calculator::Calculator(std::shared_ptr<TaylorFunction> func) : func(func) {}

Calculator::~Calculator(){}

double Calculator::lagrangeRemainder(double x, unsigned n) const {
    double maxDeriv = func->maxDerivative(n + 1, x);
    return std::abs(maxDeriv * std::pow(x, n + 1) / std::tgamma(n+2));
}

double Calculator::approximation(double x, unsigned n) const{
    x = func->prepArg(x);
    unsigned curDeg = func->firstDeg();
    if (curDeg > n){
	return 0.0;
    }
    double term = func->firstTerm(x);
    double sum = term;
    while(curDeg + 2 <= n){
	term = func->nextTerm(term, curDeg, x);
	curDeg+= 2;
	sum += term;
    }
    return sum;
}

double Calculator::compare_with_exactValue(double x, unsigned n) const{
    return std::abs(func->exactValue(x)-approximation(x, n));
}

void Calculator::setNewfunc(std::shared_ptr<TaylorFunction> func){
    this->func=func;
}
unsigned Calculator::degree(double x, double accuracy) const{
    double cur_acc;
    unsigned deg=0;
    for(; deg<=MAX_DEGREE; deg++){
        cur_acc = lagrangeRemainder(x, deg);
        if(cur_acc - accuracy <= THRESHOLD) return deg;
    }
    throw std::runtime_error("Не удалось достигнуть требуемой точности"); // тоже позже перепишу какой тут эррор
}
double Calculator::right_intervalEnd(double dx, double accuracy, unsigned n) const{
    if(dx < THRESHOLD) throw std::invalid_argument("Слишком высокая точность"); // тоже позже перепишу какой тут эррор
    double border=0.0;
    for(; lagrangeRemainder(border, n)<=accuracy; border+=dx){};
    return border;
}
double Calculator::right_intervalEnd(double dx, double accuracy) const{
    return right_intervalEnd(dx, accuracy, MAX_DEGREE);
}
double Calculator::left_intervalEnd(double dx, double accuracy, unsigned n) const{
    if(dx < THRESHOLD) throw std::invalid_argument("Слишком высокая точность"); // тоже позже перепишу какой тут эррор
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
