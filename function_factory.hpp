// function_factory.h
#pragma once
#include "taylor_function.hpp"
#include <string>
#include <memory>

class FunctionFactory {
public:
    // expr = expression - наше выражение с клавиатуры
    static std::unique_ptr<TaylorFunction> create(std::string& expr);
    
private:
    // Вспомогательная функция для извлечения коэффициента
    static double parseCoefficient(const std::string& content);
};