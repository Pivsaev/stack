#include <iostream>
#include "TStack.h"
#include "TFormula.h"

int main() {
    setlocale(LC_ALL, "Russian");
    TFormula f;
    std::cin >> f;
    try {

        int r = 0;
        double result = f.calculate(r);
        std::cout << " = " << result;
    }
    catch (int expt) {
        if (expt == 1) {
            std::cout << "Ошибка в скобках";
        }
        if (expt == 2) {
            std::cout << "две точки в числе";
        }
        if (expt == 3) {
            std::cout << "точка без цифр";
        }
        if (expt == 4) {
            std::cout << "неизвестный символ";
        }
        if (expt == 5) {
            std::cout << "переполнение буфера";
        }
        if (expt == 6) {
            std::cout << "два оператора подряд";
        }
        if (expt == 7) {
            std::cout << "деление на 0";
        }
    }
}
