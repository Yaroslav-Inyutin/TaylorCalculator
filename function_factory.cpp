#include "function_factory.hpp"
#include "sum_function.hpp"
#include "sin.hpp"
#include "cos.hpp"
#include "exp.hpp"
#include "pow.hpp"
#include "ln.hpp"
#include "sh.hpp"
#include "ch.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <memory>

using std::string;

std::shared_ptr<TaylorFunction> FunctionFactory::parse(const string& expr) {

    string clean = removeSpaces(expr); // чистим от пробелов

    std::vector<string> parts = splitByOperators(clean); // объединяем аргументы (пока ещё не обработанные) в вектор
    
    if (parts.size() == 1) { 
        // если добавили всего одну функцию, вернём её и дальше не пойдём
        auto [coeff, funcPart] = parseCoefficient(parts[0]); // parseCoeffitient возвращает std::pair - структуру из двух аргументов
        // auto [coeff, funcPart] распаковывает эту pair в две переменные: коэффициент перед функцией и строчка с ней
        // аналогично питоновскому slope, intercept = stats.linregress()

        std::shared_ptr<TaylorFunction> func = parseTerm(funcPart); // парсим  эту строчку
        
        if (coeff != 1.0) {
            auto sum = std::make_shared<SumFunction>();  // make_shared возвращает shared_ptr на новый объект SumFunction
            sum->addTerm(func, coeff);
            return sum;  // Возвращаем shared_ptr
        }
        return func;
    }
    
    auto sum = std::make_shared<SumFunction>();
    for (const std::string& part : parts) {
        if (!part.empty()) {
            auto [coeff, funcPart] = parseCoefficient(part);
            auto func = parseTerm(funcPart);
            sum->addTerm(func, coeff);
        }
    }
    return sum;
}

std::shared_ptr<TaylorFunction> FunctionFactory::parseTerm(const std::string& term) {
    size_t openParen = term.find('(');
    size_t closeParen = term.rfind(')');
    
    if (openParen == std::string::npos || closeParen == std::string::npos) {
        std::cerr << "Ошибка: неверный формат функции: " << term << std::endl;
        return std::make_shared<SinFunction>(1.0);  // ← make_shared
    }
    
    std::string funcName = term.substr(0, openParen);
    std::string argContent = term.substr(openParen + 1, closeParen - openParen - 1);
    
    double k = 1.0;
    size_t xPos = argContent.find('x');
    if (xPos != std::string::npos && xPos > 0) {
        std::string numPart = argContent.substr(0, xPos);
        if (!numPart.empty() && numPart.back() == '*') {
            numPart.pop_back();
        }
        if (!numPart.empty()) {
            try {
                k = std::stod(numPart);
            } catch (...) {
                k = 1.0;
            }
        }
    }
    
    return createFunction(funcName, k);
}

std::shared_ptr<TaylorFunction> FunctionFactory::createFunction(const std::string& funcName, double k) {
    if (funcName == "sin") {
        return std::make_shared<SinFunction>(k);  // ← make_shared
    }
    if (funcName == "cos") {
        return std::make_shared<CosFunction>(k);
    }
    if (funcName == "exp") {
        return std::make_shared<ExpFunction>(k);
    }
    
    std::cerr << "Неизвестная функция: " << funcName << std::endl;
    return std::make_shared<SinFunction>(k);
}

// ... остальные вспомогательные функции без изменений ...
std::string FunctionFactory::removeSpaces(const string& str) { /* ... */ }
std::vector<std::string> FunctionFactory::splitByOperators(const string& expr) { /* ... */ }
std::pair<double, std::string> FunctionFactory::parseCoefficient(const string& term) { /* ... */ }