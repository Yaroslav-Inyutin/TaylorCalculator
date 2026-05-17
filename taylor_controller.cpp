#include "taylor_controller.hpp"
#include <iostream>
#include "function_factory.hpp"
#include "calculator.hpp"
//using std::cout;
using std::endl;

void TaylorController::runRemainder(const std::string& input, bool useReduction, double x, unsigned n, std::ostream& out) {
    FunctionFactory factory;
    auto func = factory.create(input, useReduction);
    Calculator calc(func);
    out << endl << "==== Результаты ====" << endl;
    out << "Точность разложения (остаточный член): "<< calc.lagrangeRemainder(x, n)<< endl;
    out << "Toчное значение: "<< func->exactValue(x) << endl;
    out << "Аппроксимация: "<< calc.approximation(x, n) << endl;
    out << "Разность между точным значением и аппроксимацией: " << calc.compare_with_exactValue(x, n) << endl;
}

void TaylorController::runDegree(const std::string& input, bool useReduction, double x, double acc, std::ostream& out) {
    FunctionFactory factory;
    auto func = factory.create(input, useReduction);
    Calculator calc(func);
    unsigned n = calc.degree(x, acc);			    
    out << endl << "==== Результаты ====" << endl;			       
    out << "Требуемый порядок: " << n << endl;
    out << "Остаточный член для этого порядка: " << calc.lagrangeRemainder(x, n) << endl;
    out << "Toчное значение: "	<< func->exactValue(x) << endl;
    out << "Аппроксимация: " << calc.approximation(x, n) << endl;
}

void TaylorController::runInterval(const std::string& input, bool useReduction, double dx, double acc, unsigned n, std::ostream& out) {
    FunctionFactory factory;	       
    auto func = factory.create(input, useReduction);		  
    Calculator calc(func);		       
    out << endl << "==== Результаты ====" << endl;		
    borders bor = calc.interval(dx, acc, n);			   
    bor.printInterval();
}
