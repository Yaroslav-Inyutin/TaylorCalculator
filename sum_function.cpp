// sum_function.cpp
#include "sum_function.hpp"
#include <cmath>

SumFunction::SumFunction() : TaylorFunction(1.0) {}

SumFunction::~SumFunction() {
    for (auto& term : terms) {
        delete term.function;  // ← Было term.first
    }
    terms.clear();
}

void SumFunction::addTerm(TaylorFunction* term, double coefficient) {
    // Создаём структуру Term через конструктор
    terms.push_back(Term(term, coefficient));
}

double SumFunction::exactValue(double x) const {
    double sum = 0.0;
    for (const auto& term : terms) {
        // укоэффициент * значение функции
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