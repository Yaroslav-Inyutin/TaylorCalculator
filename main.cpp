#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include "function_factory.hpp"
#include "calculator.hpp"
#include "taylor_controller.hpp"

using std::cout, std::cin, std::endl, std::cerr;

void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

unsigned readUnsigned() {
    unsigned value;
    while (true) {
	if (cin >> value) {
	    clearInput();
            if (value <= 170) {
		return value;
	    }
	    cerr << "Слишком большой порядок разложения. Максимум: 170" << endl;
	}
	else {
	    cerr << "Введите целое неотрицательное число" << endl;
	    clearInput();
	}
    }
}

double readDouble() {
    double value;
    while (true) {
        if (cin >> value) {
            clearInput();
            return value;
	}
	else {
     	    cerr << "Введите корректное число" << endl;
            clearInput();
	}
    }
}

int main() {
    TaylorController controller;
    std::string input;

    // Бесконечный цикл — выходим только при успехе или явном выходе
    while (true) {

        // по идее, надо бы инкапсулировать эти n и x - как-то не объявлять их в main, а наверное добавлять через конструктор
        // хотя, какая разница

        try {
	    cout << "Введите функцию: ";
	    std::getline(cin, input);
	    // Пропускаем пустые вводы
	    if (input.empty()) {
		continue;
	    }

	    // Пытаемся создать функцию
	    auto func = FunctionFactory::parse(input);
	   
	    //флаг, отвечающий за использование/неиспользование оптимизации аргумента тригонометрических функций
	    bool useReduction = true;

	    if (func->isTrigonometric()) {
	    	cout << "Использовать оптимизацию аргумента для тригонометрических функций? (y/n): ";
		char answ;
		if (!(cin >> answ)) {
		    clearInput();
		    throw std::invalid_argument("Некорректный выбор режима");
		}
		clearInput();
		if (answ == 'n') {
		    useReduction = false;
		} else if (answ != 'y') {
			throw std::invalid_argument("Некорректный выбор режима");
		}
	    }
            // Спросить пользователя, какой режим выбрать.
            cout << "Выберите режим работы.\nОтправьте r, если хотите найти точность в зависимости от порядка" << endl <<
            "Отправьте n, если хотите найти минимальный порядок разложения для заданной точности." << endl <<
            "Отправьте x, если хотите найти границы интервала, на котором реализуется заданная точность. "; // это должно быть в графическом интерфейсе
            char a;
	    if (!(cin >> a)) {
		clearInput();
		throw std::invalid_argument("Такого режима нет");
	    }
	    clearInput();
	    
	    if(a!='r' && a!='n' && a!='x') {
	        throw std::invalid_argument("Такого режима нет");
	    }

            Calculator calc(func);
            if(a=='r'){
                cout << "Введите порядок разложения: ";
                unsigned n = readUnsigned();

                cout << "Введите точку, в которой функция аппроксимируется: ";
                double x = readDouble();

                controller.runRemainder(input, useReduction, x, n);
            }
            if(a=='n'){
                cout << "Введите требуемую точность: ";
                double acc = readDouble();

                cout << "Введите точку, в которой функция аппроксимируется: ";
                double x = readDouble();
                
                controller.runDegree(input, useReduction, x, acc);
            }
            if (a=='x'){
                cout << "Введите требуемую точность: ";
                double acc = readDouble();

                cout << "Введите точность вычисления границ интервала (например, 0.1): ";
                double dx = readDouble();

                cout << "Введите порядок разложения (по умолчанию: 169): ";
                unsigned n = readUnsigned();
                
                controller.runInterval(input, useReduction, dx, acc, n);
            }
            break;  // Выход из цикла после успеха
        }
        catch (const std::invalid_argument& e) {
            // Ошибка формата: пользователь ввёл что-то не то
            cerr << e.what() << endl;
            cerr << "Введите другую функцию или исправьте формат ввода.\n";
            // Цикл продолжится, cin чистить не нужно
        }
        catch (const std::runtime_error& e) {
            // Пока что это только неправильное имя переменной. Но мы поменяем этот класс, унаследуемся.
            // Кстати, можно сделать ещё другие разрешённые имена, типа y, z, t
            cerr << e.what() << endl;
            cerr << "Попробуйте другую функцию:\n";  
        }
        catch (const std::exception& e) {
            // Любой другой исключительный случай — на всякий пожарный
            cerr << "Ого! Это исключение мы еще не обработали. Исправится в будущих релизах.\nВот его лог: " << e.what();
        }
        catch (...){
            cerr << "Страшно, очень страшно. Если бы мы знали, что это такое, но мы не знаем что это такое.\nПадаем, но хотя бы не молча.";
        }
        
    }
    
    return 0;
}
