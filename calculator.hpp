#pragma once
#include "taylor_function.hpp"
#include <memory>
#include <iostream>

struct borders{
    double l,r;
    void printInterval(){
        std::cout << "Интервал заданной точности разложения: (" << l << "; " << r << ")" << std::endl;
    }
};
// этот класс, вроде бы, ничего не хранит, так что писать тут консты в суффиксах даже немного избыточно.
// не знаю, как лучше
class Calculator {
private:

    std::shared_ptr<TaylorFunction> func;
    
    double right_intervalEnd(double dx, double accuracy, unsigned n) const; // вычисляем максимальный x, на котором реализуется данная точность при заданном порядке. 
    //точность этого интервала - dx. 

    double right_intervalEnd(double dx, double accuracy) const;  // перегрузка этого метода для максимального по дефолту порядка 

    double left_intervalEnd(double dx, double accuracy, unsigned n) const;

    double left_intervalEnd(double dx, double accuracy) const;

public:

    Calculator(std::shared_ptr<TaylorFunction> func);
    ~Calculator();
    
    void setNewfunc(std::shared_ptr<TaylorFunction> func);

    // аппроксимировать функцию по Тейлору
    double approximation(double x, unsigned n); // писать тут конст или нет - зависит от того, хотим ли мы хранить аппроксимацию.
    //это эффективнее по времени исполнения, но может быть немного бесполезно и геморно в воркфлоу: там всё равно каждвя функция пересчитается несколько раз

    // сравнить аппроксимацию с cmath
    double compare_with_exactValue(double x, unsigned n); // не перегружаются, не virtual. тоже не const, потому что использует getApproximation
    
    // вычислить остаточный член в форме Лагранжа
    double lagrangeRemainder(double x, unsigned n) const; // тоже не будет перегружаться

    unsigned degree(double x, double accuracy) const; // вычисляем порядок разложения по заданной точности

    borders interval(double dx, double accuracy, unsigned n) const;
    
    borders interval(double dx, double accuracy) const;
};