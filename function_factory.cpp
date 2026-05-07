#include "function_factory.hpp"
#include "sin.hpp"
#include "cos.hpp"
#include "exp.hpp"
#include "pow.hpp"
#include "ln.hpp"
#include "sh.hpp"
#include "ch.hpp"
#include <algorithm>
#include <iostream>
// Метод ниже парсит данное ему выражение и выдаёт 
// Формат функции: пока что cos ( k x) 
std::shared_ptr<TaylorFunction> FunctionFactory::create(std::string& expr) { // Реализуем create
    
    // Убираем пробелы (erase-remove idiom)
    expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());

    auto openParen = expr.find('(');
    if (openParen == std::string::npos) {
        throw std::invalid_argument("Отсутствует открывающая скобка '('");
    }

    auto closeParen = expr.find(')', openParen); // Ищем уже с открытой скобки, что логично
    if (closeParen == std::string::npos) {
        throw std::invalid_argument("Отсутствует закрывающая скобка ')'");
    }

    // Теперь безопасно извлекать имя функции и содержимое скобок:
    std::string funcName = expr.substr(0, openParen);
    std::string content = expr.substr(openParen + 1, closeParen - openParen - 1);
    
    // Парсим коэффициент
    double k = parseCoefficient(content);
    
    // Создаём нужный объект
    if (funcName == "sin") {
        std::shared_ptr<TaylorFunction> res = std::unique_ptr<TaylorFunction>(new SinFunction(k));
        std::cout << "Найден синус\n";
        return res;
    }
    // if (funcName == "cos") {
    //     return new CosFunction(k);
    // }
    // if (funcName == "exp") {
    //     return new ExpFunction(k);
    // }
    
    throw std::invalid_argument("Не удалось распознать функцию");
}

double FunctionFactory::parseCoefficient(const std::string& content) {
    // Если просто "x" — коэффициент 1.0
    if (content == "x") {
        return 1.0;
    }
    
    // Если "-x" — коэффициент -1.0
    if (content == "-x") {
        return -1.0;
    }
    
    // Иначе ищем 'x' и берём всё до него
    auto xPos = content.find('x');
    if (xPos == std::string::npos) {
        throw std::runtime_error("Переменная функции - не x");
    }
    
    // Извлекаем числовую часть
    std::string numStr = content.substr(0, xPos);
    
    // Преобразуем в double стандартная функция stod - string to double
     return std::stod(numStr);    
}