#pragma once
#include "taylor_function.hpp"

class PowerFunction : public TaylorFunction {
private:
    double alpha_; // Сохраняем показатель степени

    // Вспомогательная функция для биномиального коэффициента C(alpha, n)
    static double binomialCoeff(double alpha, unsigned n);

public:
    explicit PowerFunction(double alpha, double k);
    ~PowerFunction() override = default; // Можно использовать default, так как нет сырых указателей

    double exactValue(double x) const override;
    double maclaurinTerm(unsigned n, double x) const override;
    
    // Возвращает оценку максимума |f^(n)(xi)| на интервале [0, x] или [-|x|, |x|]
    double maxDerivative(unsigned n, double x) const override;
};