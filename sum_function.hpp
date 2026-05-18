// класс, который будет хранить слагаемые в нашей сумме. Он "маскируется" под обычную функцию
#pragma once
#include "taylor_function.hpp"
#include <vector>
#include <string>
#include <memory>

class SumFunction : public TaylorFunction {
private:

public:
    std::vector<std::shared_ptr<TaylorFunction>> terms;  // вектор слагаемых
    
    SumFunction();
    SumFunction(std::shared_ptr<TaylorFunction> term);
    virtual ~SumFunction() override;
    
    // Копирование БЕЗОПАСНО (shared_ptr считает ссылки)
    // Можно убрать, но для ясности и для правила трёх оставим запрет
    SumFunction(const SumFunction& other) = delete;
    SumFunction& operator=(const SumFunction& other) = delete;
    
    // Добавить слагаемое
    void addTerm(std::shared_ptr<TaylorFunction> term);
    
    // Перегруженные методы базового класса
    virtual double exactValue(double x) const override;
    virtual double maxDerivative(unsigned n, double x) const override;
};