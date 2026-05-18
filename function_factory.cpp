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
#include <memory>

using std::string, std::vector, std::shared_ptr, std::make_shared;

shared_ptr<SumFunction> FunctionFactory::parse(const string& expr) {

    string clean = removeSpaces(expr); // чистим от пробелов

    vector<string> parts = splitByOperators(clean); // объединяем аргументы (пока ещё не обработанные) в вектор
    
    auto funcs = make_shared<SumFunction>();
    for(const auto& part : parts){
        funcs->addTerm(parsePart(part));
    }
    return funcs;
}

shared_ptr<TaylorFunction> FunctionFactory::parsePart(const std::string& part) {
    // Парсим слагаемое.
    // Это большая функция, работу которой неудобно разделять на многие. Отделяю комментариями отдельные её блоки
    // Ищем, где у нас скобки, x, начало функции.


    size_t openParen = part.find('(');
    if (openParen == string::npos) {
        throw std::invalid_argument("Отсутствует открывающая скобка '('");
    }

    size_t closeParen = part.rfind(')');   // поиск с конца: эффективнее
    if (closeParen == string::npos) {
        throw std::invalid_argument("Отсутствует закрывающая скобка ')'");
    }


    // Ищем знак в начале слагаемого, если есть
    int start=-1;
    double sign = 1.0;
    if(part[0] == '-'){
        start=0;
        sign=-1.0;
    }
    else if(part[0] == '+'){
        start=0;
    }
    start++; // если знак есть в начале, то start=1. если не(т, 0


    // Ищем, в какой x степени, если есть. Делаем это перед парсингом внещнего коэффициента, потому что хотим узнать 
    // положение звёздочки у степени
    double power = 0.0;

    size_t xPos = part.find('x', start);
    size_t powerEnd =0; // индекс звёздочки, если она есть. если её нет, то просто 0

    if(xPos > openParen) xPos=0; // тут мы также обрабатываем случай ненахождения x вовсе, потому что npos - это максимлаьный unsigned
    else{
        std::cout << "Найден x перед функцией" << std::endl;
        // Нашли "x" перед функцией, например "x^2*sin(5x)"

        if (part[xPos+1] == '^'){
            size_t powerStart = xPos + 2;  // символ сразу после "x^"
            powerEnd = part.find('*', powerStart);
            if (powerEnd != string::npos) {
                string powerStr = part.substr(powerStart, powerEnd - powerStart - 1);
                if(powerStr.size() != 0) power = std::stod(powerStr);  // строка → double
            }
            else throw std::invalid_argument("Неправильно введена функция"); // если нет * после степени - это обязательно
        }
        else throw std::invalid_argument("Неправильно введена функция"); // если нет ^ после x - это обязательно
    }


    // Ищем внешний коэффициент, если есть 3*x^2*sin(5x). Тоже для парсинга приходится делать звёздочку обязательной, 
    // иначе непонятно как разделять 
    double outerCoefficient;
    size_t mulPos = part.find('*', start);
    if(mulPos = string::npos || mulPos == powerEnd){
        mulPos=0;
        outerCoefficient=1.0;
    } // если звёздочек нет, или есть только у икса
    // если powerEnd == 0, то никакого x нет. Это нам подходит, в начале * быть не может
    else{
        string coefStr = part.substr(start, mulPos-start);
        outerCoefficient = std::stod(coefStr);
    }


    // Достаём название функций и их внутренность
    size_t funcStart = std::max(powerEnd, mulPos, start)+1; // x или коэффициента может просто не быть, функции тогда вернут 0


    // Теперь извлекаем имя функции и содержимое скобок:
    string funcName = part.substr(funcStart, openParen - funcStart - 1); //
    string content = part.substr(openParen + 1, closeParen - openParen - 1);
    
    double k = parseCoefficient(content); // вот здесь всё же удобно использовать функцию
    return createFunction(funcName, k, power, outerCoefficient);
}

string FunctionFactory::removeSpaces(const string& expr) { // Убираем пробелы (erase-remove idiom)
    string cleaned = expr;
    cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
    return cleaned;
}

vector<string> FunctionFactory::splitByOperators(const string& expr) {
    vector<string> parts;
    for (size_t i = 0; i < expr.length();) {
        string current;
        for(int j=0;; j++, i++){
            char c = expr[i];
            if(!(c == '+' || c== '-') || j==0){
                current.push_back(c);
            }
            else break;
        }
        parts.push_back(current);
    }
    return parts;
}

double FunctionFactory::parseCoefficient(const std::string& content){
    double k = 1.0;
    size_t xPos = content.find('x'); //ищем x в содержимом функции. возможно стоит добавить другие имена переменных
    if (xPos == string::npos || xPos < 0) throw std::runtime_error("Переменная функции - не x"); // бросаем исключения если не нашли
    // если нашли,то извлекаем численную часть
    string numPart = content.substr(0, xPos);
    if(numPart.size()==0) return k; // если ничего нет, то возвращаем единичку
    k = std::stod(numPart); // даже если там есть в конце значок умножения типа sin(3*x), stod пофигу на него
    return k;
}
shared_ptr<TaylorFunction> FunctionFactory::createFunction(const string& funcName, double k, double power, double outerCoefficient) {
    if (funcName == "sin") {
        return make_shared<SinFunction>(k, power, outerCoefficient);
    }
    if (funcName == "cos") {
        return make_shared<CosFunction>(k, power, outerCoefficient);
    }
    if (funcName == "exp") {
        return make_shared<ExpFunction>(k, power, outerCoefficient);
    }
    if (funcName == "pow") {
        return make_shared<PowerFunction>(k, power, outerCoefficient);
    }
    if (funcName == "ln") {
        return make_shared<LnFunction>(k, power, outerCoefficient);
    }
    if (funcName == "ch"){
        return make_shared<ChFunction>(k, power, outerCoefficient);
    }
    if (funcName == "sh"){
        return make_shared<ShFunction>(k, power, outerCoefficient);
    }   
    throw std::invalid_argument("Не удалось распознать функцию");
}