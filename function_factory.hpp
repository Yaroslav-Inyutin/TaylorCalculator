// function_factory.h
#pragma once
#include "taylor_function.hpp"
#include <string>
#include <memory>

class FunctionFactory {
public:
    // expr = expression - наше выражение с клавиатуры
    std::shared_ptr<TaylorFunction> create(std::string& expr, bool useReduction = true);
    
private:
    // Вспомогательная функция для извлечения коэффициента
    double parseCoefficient(const std::string& content);
};
