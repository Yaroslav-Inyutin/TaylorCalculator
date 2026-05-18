#pragma once
#include <string>

// надо подумать над эффективностью всего этого. Будем каждый раз создавать новый экземпляр класса? 
// Кажется, стоит быть умнее: создавать класс для каждого наследника единожды.
// C другой стороны, тогда каждый из этих классов зависит от своего коэффициента. Тогда надо перезаписывать его каждый раз при чтении функции

class TaylorFunction {

protected:
    double coefficient;  // k в f(kx)
    double outerCoefficient; // a в a*f(x)
    double power;  // степень x перед функцией (0 по умолчанию)

public:
    // Конструктор со списком инициализации
    explicit TaylorFunction(double k, double power, double outerCoefficient);
    
    // Виртуальный деструктор 
    virtual ~TaylorFunction()=0;
    
    // Значение функции в заданной точке из сmath
    virtual double exactValue(double x) const=0;


    // Легаси из прошлой версииф
    //static double factorial(unsigned n); // перегружаться в наследниках не будет, поэтому не virtual.

    //static const unsigned MAX_EXACT_FACTORIAL = 20;

    //static const unsigned MAX_FACTORIAL = 170;

    // вычисление n-ого члена в разложении Маклорена - своего для каждой функции, поэтому virtual=0
    //virtual double maclaurinTerm(unsigned n, double x) const = 0; //

    virtual double maxDerivative(unsigned n, double x) const = 0; // вычисляет максимальную производную на отрезке
    
    //будет приводить аргументы тригонометрических функций к [-pi, pi]
    virtual double prepArg(double x) const;

    //первый ненулевой член разложения
    virtual double firstTerm(double x) const = 0;

    //первая ненулевая степень
    virtual unsigned firstDeg() const = 0;

    //следующий член
    virtual double nextTerm(double prevTerm, unsigned prevN, double x) const = 0;

    virtual bool isTrigonometric() const;

    double getPower(){
        return power;
    }
    double getOuterCoefficient(){
        return outerCoefficient;
    }
};
