#pragma once
#include <string>

class SeriesFunction {
protected:
    double coefficient;  // k в f(kx)
    
public:
    // Конструктор со списком инициализации
    explicit SeriesFunction(double k = 1.0);
    
    // Виртуальный деструктор 
    virtual ~SeriesFunction();
    
    virtual double evaluate(double x) const = 0;

    virtual double maclaurinTerm(unsigned n, double x) const = 0; //

    virtual double maxDerivative(unsigned n, double intervalEnd) const = 0; // вычисляет максимальную производную на отрезкке

    virtual std::string name() const = 0;
    
    double lagrangeRemainder(unsigned n, double x) const; // вычисляет остаточный член в форме Лагранжа
    
    double getCoefficient() const; // геттер
};