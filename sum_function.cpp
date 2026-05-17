// sum_function.cpp
#include "sum_function.hpp"
#include <cmath>
#include <memory>

SumFunction::SumFunction() : TaylorFunction(1.0) {}

SumFunction::~SumFunction() = default;

void SumFunction::addTerm(std::shared_ptr<TaylorFunction> term, double coefficient) {
    // Создаём структуру Term через конструктор
    terms.emplace_back(Term(term, coefficient)); // emplace чуть эффективнее push
}
SumFunction::SumFunction(std::shared_ptr<TaylorFunction> term, double coefficient) : TaylorFunction(1.0){
    // конструктор, который сразу закидывает один объект
    addTerm(term, coefficient);
}
double SumFunction::exactValue(double x) const {
    double sum = 0.0;
    for (const auto& term : terms) {
        // коэффициент * значение функции
        sum += term.coefficient * term.function->exactValue(x);
    }
    return sum;
}

double SumFunction::maxDerivative(unsigned n, double intervalEnd) const {
    double sum = 0.0;
    for (const auto& term : terms) {
        sum += term.coefficient * term.function->maxDerivative(n, intervalEnd);
    }
    return sum;
}