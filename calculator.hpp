#pragma once
#include "taylor_function.hpp"
#include <memory>


// этот класс, вроде бы, ничего не хранит, так что писать тут консты в суффиксах даже немного избыточно.
// не знаю, как лучше
class Calculator {
private:
    std::shared_ptr<TaylorFunction> func;
public:
    Calculator(std::shared_ptr<TaylorFunction> func);
    ~Calculator();
    
    void setNewfunc(std::shared_ptr<TaylorFunction> func);

    // аппроксимировать функцию по Тейлору
    double approximation(const double& x, const unsigned& n); // писать тут конст или нет - зависит от того, хотим ли мы хранить аппроксимацию.
    //это эффективнее по времени исполнения, но может быть немного бесполезно и геморно в воркфлоу: там всё равно каждвя функция пересчитается несколько раз

    // сравнить аппроксимацию с cmath
    double compare_with_exactValue(const double& x, const unsigned& n); // не перегружаются, не virtual. тоже не const, потому что использует getApproximation
    
    // вычислить остаточный член в форме Лагранжа
    double lagrangeRemainder(const double& x, const unsigned& n) const; // тоже не будет перегружаться

    unsigned degree(const double& accuracy, const double& x) const; // вычисляем порядок разложения по заданной точности
};