#pragma once
#include <string>

// надо подумать над эффективностью всего этого. Будем каждый раз создавать новый экземпляр класса? 
// Кажется, стоит быть умнее: создавать класс для каждого наследника единожды.
// C другой стороны, тогда каждый из этих классов зависит от своего коэффициента. Тогда надо перезаписывать его каждый раз при чтении функции
class TaylorFunction {
protected:
    double coefficient;  // k в f(kx)
    static double factorial(unsigned n);
    static const unsigned MAX_EXACT_FACTORIAL = 20;

    // вычисление n-ого члена в разложении Маклорена - своего для каждой функции
    virtual double maclaurinTerm(const unsigned n, const double x) const = 0; //

    virtual double maxDerivative(const unsigned n, const double x) const = 0; // вычисляет максимальную производную на отрезке
    
public:
    // Конструктор со списком инициализации
    explicit TaylorFunction(double k = 1.0);
    
    // Виртуальный деструктор 
    virtual ~TaylorFunction() =0;
    
    // Значение функции в заданной точке из сmath
    virtual double exactValue(const double x) const = 0;

    virtual double getApproximation(const double x, const unsigned n) const;
    virtual double compare_with_exactValue(const double x, const unsigned n) const; // кстати, а зачем тут виртуальность? мы же не будем переопределять эту функцию
    // virtual std::string name() const = 0;
    
    virtual double lagrangeRemainder(const unsigned n, const double x) const; // вычисляет остаточный член в форме Лагранжа
    // virtual double getCoefficient() const; // геттер
};