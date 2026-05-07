#pragma once
#include <string>

// надо подумать над эффективностью всего этого. Будем каждый раз создавать новый экземпляр класса? 
// Кажется, стоит быть умнее: создавать класс для каждого наследника единожды.
// C другой стороны, тогда каждый из этих классов зависит от своего коэффициента. Тогда надо перезаписывать его каждый раз при чтении функции
class TaylorFunction {

protected:
    double coefficient;  // k в f(kx)

public:
    // Конструктор со списком инициализации
    explicit TaylorFunction(double k);
    
    // Виртуальный деструктор 
    virtual ~TaylorFunction()=0;
    
    // Значение функции в заданной точке из сmath
    virtual double exactValue(const double x) const=0;

    static double factorial(const unsigned& n); // перегружаться в наследниках не будет, поэтому не virtual.

    // вычисление n-ого члена в разложении Маклорена - своего для каждой функции, поэтому virtual=0
    virtual double maclaurinTerm(const unsigned& n, const double& x) const = 0; //

    virtual double maxDerivative(const unsigned& n, const double& x) const = 0; // вычисляет максимальную производную на отрезке

    static const unsigned MAX_EXACT_FACTORIAL = 20;

    static const unsigned MAX_FACTORIAL = 170;
};