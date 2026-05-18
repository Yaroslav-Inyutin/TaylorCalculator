#include "taylor_controller.hpp"
#include <iostream>
#include "function_factory.hpp"
#include "calculator.hpp"
using std::cout;
using std::endl;

void TaylorController::runRemainder(const std::string& input, bool useReduction, double x, unsigned n) {
    FunctionFactory factory;
    auto func = factory.parse(input);
    Calculator calc(func);
    cout << endl << "==== Результаты ====" << endl;
    cout << "Точность разложения (остаточный член): "<< calc.lagrangeRemainder(x, n)<< endl;
    cout << "Toчное значение: "<< func->exactValue(x) << endl;
    cout << "Аппроксимация: "<< calc.approximation(x, n) << endl;
    cout << "Разность между точным значением и аппроксимацией: " << calc.compare_with_exactValue(x, n) << endl;
}

void TaylorController::runDegree(const std::string& input, bool useReduction, double x, double acc) {
    FunctionFactory factory;
    auto func = factory.parse(input);
    Calculator calc(func);
    unsigned n = calc.degree(x, acc);			    
    cout << endl << "==== Результаты ====" << endl;			       
    cout << "Требуемый порядок: " << n << endl;
    cout << "Остаточный член для этого порядка: " << calc.lagrangeRemainder(x, n) << endl;
    cout << "Toчное значение: "	<< func->exactValue(x) << endl;
    cout << "Аппроксимация: " << calc.approximation(x, n) << endl;
}

void TaylorController::runInterval(const std::string& input, bool useReduction, double dx, double acc, unsigned n) {
    FunctionFactory factory;	       
    auto func = factory.parse(input);		  
    Calculator calc(func);		       
    cout << endl << "==== Результаты ====" << endl;		
    borders bor = calc.interval(dx, acc, n);			   
    bor.printInterval();
}
