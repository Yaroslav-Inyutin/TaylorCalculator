// sum_function.cpp
#include "sum_function.hpp"
#include <cmath>
#include <memory>

SumFunction::SumFunction() : TaylorFunction(1.0, 1.0, 1.0) {}

SumFunction::~SumFunction() = default;

void SumFunction::addTerm(std::shared_ptr<TaylorFunction> term) {
    // закидываем функции в вектор
    terms.emplace_back(term); // emplace чуть эффективнее push
}
SumFunction::SumFunction(std::shared_ptr<TaylorFunction> term) : TaylorFunction(1.0, 1.0, 1.0){
    // конструктор, который сразу закидывает один объект
    addTerm(term);
}
double SumFunction::exactValue(double x) const {
    double sum = 0.0;
    for (const auto& term : terms) {
        // коэффициент * x^a * значение функции
        sum += term->getOuterCoefficient() * std::pow(x, term->getPower()) * term->exactValue(x);
    }
    return sum;
}

double SumFunction::maxDerivative(unsigned n, double x) const {
    double sum = 0.0;
    for (const auto& term : terms) {
        sum += term->getOuterCoefficient() * std::pow(x, term->getPower()) * term->maxDerivative(n, x);
    }
    return sum;
}
double SumFunction::firstTerm(double x) const {
    return 0.0;
}
unsigned SumFunction::firstDeg() const {
    return 0;
}
double SumFunction::nextTerm(double prevTerm, unsigned prevN, double x) const{
    return 0.0;
}