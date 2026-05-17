// парсер
#pragma once
#include "taylor_function.hpp"
#include <string>
#include <vector>
#include <utility>
#include <memory>  // Для shared_ptr

class FunctionFactory {
public:
    // Возвращаем shared_ptr — владелец передаётся наружу
    static std::shared_ptr<TaylorFunction> parse(const std::string& expr);
    
private:
    static std::string removeSpaces(const std::string& str);
    static std::vector<std::string> splitByOperators(const std::string& expr);
    static std::pair<double, std::string> parseCoefficient(const std::string& term);
    static std::shared_ptr<TaylorFunction> parseTerm(const std::string& term);
    static std::shared_ptr<TaylorFunction> createFunction(const std::string& funcName, double k);
};