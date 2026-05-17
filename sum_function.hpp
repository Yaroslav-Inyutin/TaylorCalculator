// класс, который будет хранить слагаемые в нашей сумме
#pragma once
#include "taylor_function.hpp"
#include <vector>
#include <string>

// Структура для хранения слагаемого: функция + коэффициент
struct Term { 
    TaylorFunction* function;   // Указатель на функцию (sin, cos, exp...)
    double coefficient;         // Коэффициент перед функцией (например, 3 в 3*sin(x))
    
    // Конструктор со списком инициализации
    Term(TaylorFunction* func, double coeff) : function(func), coefficient(coeff) {}
};

class SumFunction : public TaylorFunction {
private:
    std::vector<Term> terms;  // вектор слагаемых

public:
    SumFunction();
    virtual ~SumFunction() override;
    
    // Запрет копирования - урезанный аналог правила трёх, вместо реализации всех 
    // троих методов для избежания некорректной работы с памятью мы просто запрещаем копирование
    // - код не компилируется, если попробовать скопировать этот класс
    SumFunction(const SumFunction& other) = delete;
    SumFunction& operator=(const SumFunction& other) = delete;
    
    // Добавить слагаемое
    void addTerm(TaylorFunction* term, double coefficient);
    
    // Перегруженные методы базового класса
    virtual double exactValue(double x) const override;
    virtual double maxDerivative(unsigned n, double intervalEnd) const override;
};