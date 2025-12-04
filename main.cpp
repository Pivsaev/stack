#include <iostream>
#include "TStack.h"
#include "TFormula.h"

int main() {
    TFormula f;
    std::cin >> f;
    try {
        char* postfix = f.Postfix();
        int r = 0;
        std::cout << postfix;
        double result = f.calculate(r);
        std::cout << " = " << result;
        delete[] postfix;
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
    }
}
