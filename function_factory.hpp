// парсер
#pragma once
#include "sum_function.hpp"
#include <string>
#include <vector>
#include <utility>
#include <memory>  // Для shared_ptr


class FunctionFactory {
public:
    // Возвращаем shared_ptr — владелец передаётся наружу
    static std::shared_ptr<SumFunction> parse(const std::string& expr);
    
private:
    static std::string removeSpaces(const std::string& str);
    static std::vector<std::string> splitByOperators(const std::string& expr);
    static std::shared_ptr<TaylorFunction> parsePart(const std::string& term);
    static double parseCoefficient(const std::string& content);
    static std::shared_ptr<TaylorFunction> createFunction(const std::string& funcName, double k, double power, double outerCoefficient);
};