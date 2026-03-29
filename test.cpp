#include <iostream>
using std::string, std::cin, std::cout;

class Calculator{
    // Пока что только Маклорен
private:

protected:

double error;
unsigned degree;
string expression;
double x;

public:

Calculator(const string& expression, const unsigned& degree, const double& x): expression(expression), degree(degree), x(x){}
Calculator(const string& expression, const double& error, const double& x): expression(expression), error(error), x(x){}

~Calculator(){}
// Функции, которые я хочу включить в данный момент - sin, cos, sh, ch, tg, ctg, th, cth, exp (kx) k - число вида 3 или 2.2
Interpreter

};
int main(){

}