#pragma once
#include "sum_function.hpp"
#include <memory>
#include <iostream>

struct borders{
    double l,r;
    void printInterval(){
        std::cout << "Интервал заданной точности разложения: (" << l << "; " << r << ")" << std::endl;
    }
};

class Calculator {
private:

    std::shared_ptr<SumFunction> func;
    
    double right_intervalEnd(double dx, double accuracy, unsigned n) const; // вычисляем максимальный x, на котором реализуется данная точность при заданном порядке. 
    //точность этого интервала - dx. 

    double right_intervalEnd(double dx, double accuracy) const;  // перегрузка этого метода для максимального по дефолту порядка 

    double left_intervalEnd(double dx, double accuracy, unsigned n) const;

    double left_intervalEnd(double dx, double accuracy) const;

public:

    Calculator(std::shared_ptr<SumFunction> func);
    ~Calculator();
    
    void setNewfunc(std::shared_ptr<SumFunction> func);

    // аппроксимировать функцию по Тейлору
    double approximation(double x, unsigned n) const; 

    // сравнить аппроксимацию с cmath
    double compare_with_exactValue(double x, unsigned n) const; 

    // вычислить остаточный член в форме Лагранжа
    double lagrangeRemainder(double x, unsigned n) const; 

    unsigned degree(double x, double accuracy) const; // вычисляем порядок разложения по заданной точности

    borders interval(double dx, double accuracy, unsigned n) const; // находим интервал, где соблюдается точносnm
    
    borders interval(double dx, double accuracy) const;
};
