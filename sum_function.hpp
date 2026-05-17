// класс, который будет хранить слагаемые в нашей сумме
#pragma once
#include "taylor_function.hpp"
#include <vector>
#include <string>
#include <memory>

// Структура для хранения слагаемого: функция + коэффициент
struct Term { 
    std::shared_ptr<TaylorFunction> function;   // Указатель на функцию (sin, cos, exp...)
    double coefficient;         // Коэффициент перед функцией (например, 3 в 3*sin(x))
    
    // Конструктор со списком инициализации
    Term(std::shared_ptr<TaylorFunction> func, double coeff) : function(func), coefficient(coeff) {}
};

class SumFunction : public TaylorFunction {
private:
    std::vector<Term> terms;  // вектор слагаемых

public:
    SumFunction();
    SumFunction(std::shared_ptr<TaylorFunction> term, double coefficient);
    virtual ~SumFunction() override;
    
    // Копирование БЕЗОПАСНО (shared_ptr считает ссылки)
    // Можно убрать, но для ясности и для правила трёх оставим запрет
    SumFunction(const SumFunction& other) = delete;
    SumFunction& operator=(const SumFunction& other) = delete;
    
    // Добавить слагаемое
    void addTerm(std::shared_ptr<TaylorFunction> term, double coefficient);
    
    // Перегруженные методы базового класса
    virtual double exactValue(double x) const override;
    virtual double maxDerivative(unsigned n, double intervalEnd) const override;
};