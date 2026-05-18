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
        throw std::invalid_argument("Отсутствует открывающая скобка '('\nЕсли на самом деле она есть - скорее всего, вы ввели неправильный формат функции.");
    }

    size_t closeParen = part.rfind(')');   // поиск с конца: эффективнее
    if (closeParen == string::npos) {
        // std::cout << "Бросаю исключение на закрывающую скобку" << std::endl;
        throw std::invalid_argument("Отсутствует закрывающая скобка ')'\nЕсли на самом деле она есть - скорее всего, вы ввели неправильный формат функции.");
    }


    // Ищем знак в начале слагаемого, если есть
    size_t start = -1;
    double sign = 1.0;
    if(part[0] == '-'){
        start = 0;
        sign = -1.0;
    }
    else if(part[0] == '+'){
        start = 0;
    }
    start++; // если знак есть в начале, то start=1. если нет, 0


    // Ищем, в какой x степени, если есть. Делаем это перед парсингом внещнего коэффициента, потому что хотим узнать 
    // положение звёздочки у степени
    double power = 0.0;
    bool xExists = false;
    size_t xPos = part.find('x', start);
    size_t powerEnd = 0; // индекс звёздочки, если она есть. если её нет, то просто 0

    if(xPos > openParen || part[xPos+1] == 'p') xPos = 0; // тут мы также обрабатываем случай ненахождения x вовсе, 
    // потому что npos - это максимлаьный unsigned. Кроме того, тут же надо проверить, что этот x не часть фразы exp
    else{
        xExists=true;
        std::cout << "Найден x перед функцией" << std::endl;
        // Нашли "x" перед функцией, например "x^2*sin(5x)"

        if (part[xPos+1] == '^'){
            size_t powerStart = xPos + 2;  // символ сразу после "x^"
            powerEnd = part.find('*', powerStart);
            if (powerEnd != string::npos) {
                string powerStr = part.substr(powerStart, powerEnd - powerStart); // убран лишний -1
                if(powerStr.size() != 0) power = std::stod(powerStr);  // строка → double
            }
            else throw std::invalid_argument("Неправильно введена функция. Не хватает * после x^a."); // если нет * после степени - это обязательно
        }
        else{
            power=1.0;
            powerEnd=xPos+1;
        }
    }


    // Ищем внешний коэффициент, если есть 3*x^2*sin(5x). Тоже для парсинга приходится делать звёздочку обязательной, 
    // иначе непонятно как разделять 
    double outerCoefficient;
    bool coeffExists=false;
    size_t mulPos = part.find('*', start);
    if(mulPos == string::npos || mulPos == powerEnd){
        mulPos = 0;
        outerCoefficient = 1.0;
    } // если звёздочек нет, или есть только у икса
    // если powerEnd == 0, то никакого x нет. Это нам подходит, в начале * быть не может
    else{
        coeffExists=true;
        string coefStr = part.substr(start, mulPos - start);
        outerCoefficient = std::stod(coefStr);
    }


    // Достаём точку начала функции
    size_t funcStart;
    if(xExists) funcStart=powerEnd+1;
    else if(coeffExists) funcStart=mulPos+1;
    else funcStart=start;


    // Теперь извлекаем имя функции и содержимое скобок:
    string funcName = part.substr(funcStart, openParen - funcStart); // убран лишний -1
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
    size_t i = 0;
    while (i < expr.length()) {
        string current;
        current += expr[i++]; // Нулевой символ (возможно знак) всегда включаем, потом инкрементим i и идём дальше
        
        while (i < expr.length()) {
            char c = expr[i];
            // Если встретили + или - как разделитель (не первый символ терма)
            if ((c == '+' || c == '-') && !current.empty()) {
                break;
            }
            current += c;
            i++;
        }
        if(!current.empty()) {
            parts.push_back(current);
        }
    }
    return parts;
}

double FunctionFactory::parseCoefficient(const std::string& content){
    double k = 1.0;
    size_t xPos = content.find('x'); //ищем x в содержимом функции. возможно стоит добавить другие имена переменных
    if (xPos == string::npos) throw std::invalid_argument("Переменная функции - не x"); // бросаем исключения если не нашли
    // если нашли,то извлекаем численную часть
    string numPart = content.substr(0, xPos);
    if(numPart.size() == 0) return k; // если ничего нет, то возвращаем единичку
    k = std::stod(numPart); // даже если там есть в конце значок умножения типа sin(3*x), stod пофигу на него
    return k;
}

shared_ptr<TaylorFunction> FunctionFactory::createFunction(const string& funcName, double k, double power, double outerCoefficient) {
    std::cout << "Имя функции: " << funcName << std::endl;
    if (funcName == "sin") {
        return make_shared<SinFunction>(k, power, outerCoefficient);
    }
    if (funcName == "cos") {
        return make_shared<CosFunction>(k, power, outerCoefficient);
    }
    if (funcName == "exp") {
        return make_shared<ExpFunction>(k, power, outerCoefficient);
    }
    // if (funcName == "pow") {
    //     return make_shared<PowerFunction>(k, power, outerCoefficient);
    // }
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