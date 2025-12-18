#include <iostream>
#include "TStack.h"
#include "TFormula.h"

int main() {
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
        else if (expt == 2) {
            std::cout << "две точки в числе";
        }
        else if (expt == 3) {
            std::cout << "точка без цифр";
        }
        else if (expt == 4) {
            std::cout << "неизвестный символ";
        }
        else if (expt == 5) {
            std::cout << "переполнение буфера";
        }
        else if (expt == 6) {
            std::cout << "два оператора подряд";
        }
        else if (expt == 7) {
            std::cout << "деление на 0";
        }
        else if (expt == 8) {
            std::cout << "пропущен оператор";
        }
        else if (expt == 9) {
            std::cout << "оператор без операнда слева";
        }
        else if (expt == 10) {
            std::cout << "оператор перед закрывающей скобкой";
        }
        else if (expt == 11) {
            std::cout << "оператор в конце выражения";
        }
        else if (expt == 12) {
            std::cout << "недостаточно операндов";
        }
        else if (expt == 13) {
            std::cout << "ошибка в вычислении";
        }
    }
}
